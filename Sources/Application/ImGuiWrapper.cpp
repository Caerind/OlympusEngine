#include "ImGuiWrapper.hpp"

#include <SFML/OpenGL.hpp>

namespace oe
{

namespace ImGuiWrapper
{

static bool s_mousePressed[3] = { false, false, false };
static sf::Texture* s_fontTexture = nullptr;

void init()
{
	ImGuiIO& io = ImGui::GetIO();

	// init io
	io.IniFilename = nullptr;

	// init keyboard mapping
	io.KeyMap[ImGuiKey_Tab] = sf::Keyboard::Tab;
	io.KeyMap[ImGuiKey_LeftArrow] = sf::Keyboard::Left;
	io.KeyMap[ImGuiKey_RightArrow] = sf::Keyboard::Right;
	io.KeyMap[ImGuiKey_UpArrow] = sf::Keyboard::Up;
	io.KeyMap[ImGuiKey_DownArrow] = sf::Keyboard::Down;
	io.KeyMap[ImGuiKey_PageUp] = sf::Keyboard::PageUp;
	io.KeyMap[ImGuiKey_PageDown] = sf::Keyboard::PageDown;
	io.KeyMap[ImGuiKey_Home] = sf::Keyboard::Home;
	io.KeyMap[ImGuiKey_End] = sf::Keyboard::End;
	io.KeyMap[ImGuiKey_Delete] = sf::Keyboard::Delete;
	io.KeyMap[ImGuiKey_Backspace] = sf::Keyboard::BackSpace;
	io.KeyMap[ImGuiKey_Enter] = sf::Keyboard::Return;
	io.KeyMap[ImGuiKey_Escape] = sf::Keyboard::Escape;
	io.KeyMap[ImGuiKey_A] = sf::Keyboard::A;
	io.KeyMap[ImGuiKey_C] = sf::Keyboard::C;
	io.KeyMap[ImGuiKey_V] = sf::Keyboard::V;
	io.KeyMap[ImGuiKey_X] = sf::Keyboard::X;
	io.KeyMap[ImGuiKey_Y] = sf::Keyboard::Y;
	io.KeyMap[ImGuiKey_Z] = sf::Keyboard::Z;

	// init texture
	if (s_fontTexture == nullptr)
	{
		s_fontTexture = new sf::Texture();
		unsigned char* pixels;
		int width, height;
		io.Fonts->GetTexDataAsRGBA32(&pixels, &width, &height);
		s_fontTexture->create(width, height);
		s_fontTexture->update(pixels);
		io.Fonts->ClearInputData();
		io.Fonts->ClearTexData();
		io.Fonts->TexID = (void*)s_fontTexture->getNativeHandle();
	}
}

void handleEvent(sf::RenderWindow& window, const sf::Event& event)
{
	ImGuiIO& io = ImGui::GetIO();
	if (window.hasFocus())
	{
		switch (event.type)
		{
			case sf::Event::MouseButtonPressed: // fall-through
			case sf::Event::MouseButtonReleased:
			{
				int button = event.mouseButton.button;
				if (event.type == sf::Event::MouseButtonPressed && button >= 0 && button < 3)
				{
					s_mousePressed[event.mouseButton.button] = true;
				}
			}
			break;

			case sf::Event::MouseWheelMoved:
				io.MouseWheel += static_cast<float>(event.mouseWheel.delta);
				break;

			case sf::Event::KeyPressed: // fall-through
			case sf::Event::KeyReleased:
				io.KeysDown[event.key.code] = (event.type == sf::Event::KeyPressed);
				io.KeyCtrl = event.key.control;
				io.KeyShift = event.key.shift;
				io.KeyAlt = event.key.alt;
				break;

			case sf::Event::TextEntered:
				if (event.text.unicode > 0 && event.text.unicode < 0x10000)
				{
					io.AddInputCharacter(static_cast<ImWchar>(event.text.unicode));
				}
				break;

			default: break;
		}
	}
}

void update(sf::RenderWindow& window, sf::Time dt)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DisplaySize = static_cast<sf::Vector2f>(window.getSize());
	io.DeltaTime = dt.asSeconds();

	if (window.hasFocus())
	{
		io.MousePos = sf::Mouse::getPosition(window);
		for (int i = 0; i < 3; i++)
		{
			io.MouseDown[i] = s_mousePressed[i] || sf::Mouse::isButtonPressed((sf::Mouse::Button)i);
			s_mousePressed[i] = false;
		}
	}

	ImGui::NewFrame();
}

void updateRender()
{
	ImGui::Render();
}

void render()
{
	ImDrawData* draw_data = ImGui::GetDrawData();
	if (draw_data == nullptr || draw_data->CmdListsCount == 0)
	{
		return;
	}

	ImGuiIO& io = ImGui::GetIO();
	assert(io.Fonts->TexID != nullptr);

	// scale stuff (needed for proper handling of window resize)
	int fb_width = static_cast<int>(io.DisplaySize.x * io.DisplayFramebufferScale.x);
	int fb_height = static_cast<int>(io.DisplaySize.y * io.DisplayFramebufferScale.y);
	if (fb_width == 0 || fb_height == 0) { return; }
	draw_data->ScaleClipRects(io.DisplayFramebufferScale);

	// Save OpenGL state
	GLint last_viewport[4]; glGetIntegerv(GL_VIEWPORT, last_viewport);
	GLint last_texture; glGetIntegerv(GL_TEXTURE_BINDING_2D, &last_texture);
	GLint last_scissor_box[4]; glGetIntegerv(GL_SCISSOR_BOX, last_scissor_box);

	glPushAttrib(GL_ENABLE_BIT | GL_COLOR_BUFFER_BIT | GL_TRANSFORM_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_SCISSOR_TEST);
	glEnable(GL_TEXTURE_2D);

	glViewport(0, 0, (GLsizei)fb_width, (GLsizei)fb_height);

	glMatrixMode(GL_TEXTURE);
	glPushMatrix();
	glLoadIdentity();

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0f, io.DisplaySize.x, io.DisplaySize.y, 0.0f, -1.0f, +1.0f);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	for (int n = 0; n < draw_data->CmdListsCount; n++)
	{
		const ImDrawList* cmd_list = draw_data->CmdLists[n];
		const unsigned char* vtx_buffer = (const unsigned char*)&cmd_list->VtxBuffer.front();
		const ImDrawIdx* idx_buffer = &cmd_list->IdxBuffer.front();

		glVertexPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, pos)));
		glTexCoordPointer(2, GL_FLOAT, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, uv)));
		glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(ImDrawVert), (void*)(vtx_buffer + offsetof(ImDrawVert, col)));

		for (int cmd_i = 0; cmd_i < cmd_list->CmdBuffer.size(); cmd_i++)
		{
			const ImDrawCmd* pcmd = &cmd_list->CmdBuffer[cmd_i];
			if (pcmd->UserCallback)
			{
				pcmd->UserCallback(cmd_list, pcmd);
			}
			else
			{
				GLuint tex_id = (GLuint)*((unsigned int*)&pcmd->TextureId);
				glBindTexture(GL_TEXTURE_2D, tex_id);
				glScissor((int)pcmd->ClipRect.x, (int)(fb_height - pcmd->ClipRect.w), (int)(pcmd->ClipRect.z - pcmd->ClipRect.x), (int)(pcmd->ClipRect.w - pcmd->ClipRect.y));
				glDrawElements(GL_TRIANGLES, (GLsizei)pcmd->ElemCount, GL_UNSIGNED_SHORT, idx_buffer);
			}
			idx_buffer += pcmd->ElemCount;
		}
	}

	// Restore modified state
	glBindTexture(GL_TEXTURE_2D, (GLuint)last_texture);
	glMatrixMode(GL_TEXTURE);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glPopAttrib();
	glViewport(last_viewport[0], last_viewport[1], (GLsizei)last_viewport[2], (GLsizei)last_viewport[3]);
	glScissor(last_scissor_box[0], last_scissor_box[1], (GLsizei)last_scissor_box[2], (GLsizei)last_scissor_box[3]);
}

void shutdown()
{
	ImGui::GetIO().Fonts->TexID = nullptr;

	// if internal texture was created, we delete it
	if (s_fontTexture != nullptr)
	{
		delete s_fontTexture;
		s_fontTexture = nullptr;
	}

	ImGui::Shutdown();
}

} // namespace ImGuiWrapper



ImGuiWindow::ImGuiWindow(const std::string& name, F32 x, F32 y, F32 w, F32 h)
	: mName(name)
	, mVisible(false)
	, mX(x)
	, mY(y)
	, mW(w)
	, mH(h)
{
}

void ImGuiWindow::show()
{
	mVisible = true;
}

void ImGuiWindow::hide()
{
	mVisible = false;
}

bool ImGuiWindow::isVisible() const
{
	return mVisible;
}

const std::string& ImGuiWindow::getName() const
{
	return mName;
}

void ImGuiWindow::Begin(F32 x, F32 y, F32 w, F32 h)
{
	if (mX != -1.0f && mY != -1.0f)
	{
		ImGui::SetNextWindowPos(ImVec2(mX, mY), ImGuiSetCond_FirstUseEver);
	}
	else
	{
		ImGui::SetNextWindowPos(ImVec2(x, y), ImGuiSetCond_FirstUseEver);
	}

	if (mW != -1.0f && mH != -1.0f)
	{
		ImGui::SetNextWindowSize(ImVec2(mW, mH), ImGuiSetCond_FirstUseEver);
	}
	else
	{
		ImGui::SetNextWindowSize(ImVec2(w, h), ImGuiSetCond_FirstUseEver);
	}

	ImGui::Begin(getName().c_str());
}

ImGuiLogger::ImGuiLogger(F32 x, F32 y, F32 w, F32 h)
	: ImGuiWindow("Logger", x, y, w, h)
	, LogReceiver()
{
}

ImGuiLogger::~ImGuiLogger()
{
	if (isConnected())
	{
		disconnect();
	}
	clear();
}

void ImGuiLogger::onReceive(const Log& log)
{
	mLines.push_back('[' + log.type + "]: " + log.message + '\n');
}

void ImGuiLogger::draw()
{
	if (isVisible())
	{
		ImGuiWindow::Begin(10, 10, 300, 200);

		if (ImGui::Button("Clear"))
		{
			clear();
		}

		ImGui::BeginChild("Scrolling", ImVec2(0, 0), true, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		for (U32 i = 0; i < mLines.size(); i++)
		{
			ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
			if (mLines[i].find("[ERROR]") != std::string::npos) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
			else if (mLines[i].find("[WARNING]") != std::string::npos) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, col);
			ImGui::TextUnformatted(mLines[i].c_str());
			ImGui::PopStyleColor();
		}
		ImGui::PopStyleVar();
		ImGui::EndChild();

		ImGui::End();
	}
}

void ImGuiLogger::clear()
{
	mLines.clear();
}

ImGuiConsole::ImGuiConsole(F32 x, F32 y, F32 w, F32 h)
	: ImGuiWindow("Console", x, y, w, h)
	, ConsoleInstance()
{
	clearLines();
	memset(mInputBuf, 0, sizeof(mInputBuf));
	addLine("Welcome to ImGui!");
	addLine("Enter 'help' for help");
}

ImGuiConsole::~ImGuiConsole()
{
	if (isConnected())
	{
		disconnect();
	}
	clearLines();
}

void ImGuiConsole::clearLines()
{
	mLines.clear();
}

void ImGuiConsole::addLine(const std::string& line)
{
	mLines.push_back(line);
}

void ImGuiConsole::draw()
{
	if (isVisible())
	{
		ImGuiWindow::Begin(10, 220, 300, 200);

		if (ImGui::Button("Clear"))
		{
			clearLines();
		}

		ImGui::BeginChild("Scrolling", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing
		for (U32 i = 0; i < mLines.size(); i++)
		{
			ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // A better implementation may store a type per-item. For the sample let's just parse the text.
			if (mLines[i].find("[error]") != std::string::npos) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
			else if (mLines[i].find("# ") != std::string::npos) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
			ImGui::PushStyleColor(ImGuiCol_Text, col);
			ImGui::TextUnformatted(mLines[i].c_str());
			ImGui::PopStyleColor();
		}
		ImGui::PopStyleVar();
		ImGui::EndChild();
		ImGui::Separator();

		// Command-line
		if (ImGui::InputText("Input", mInputBuf, 256, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			sendCommand(std::string(mInputBuf));
			#ifdef _MSC_VER
                strcpy_s(mInputBuf, "");
            #else
                strcpy(mInputBuf, "");
            #endif
		}

		// Keep auto focus on the input box
		if (ImGui::IsItemHovered() || (ImGui::IsRootWindowOrAnyChildFocused() && !ImGui::IsAnyItemActive() && !ImGui::IsMouseClicked(0)))
		{
			ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget
		}

		ImGui::End();
	}
}

ImGuiProfiler::ImGuiProfiler(F32 x, F32 y, F32 w, F32 h)
	: ImGuiWindow("Profiler", x, y, w, h)
	, ProfilerDisplay()
	, mPaused(false)
	, mImportant(true)
{
}

ImGuiProfiler::~ImGuiProfiler()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ImGuiProfiler::displayFrame(const ProfilerFrame& frame)
{
	if (!mPaused)
	{
		if (!mImportant || (mImportant && frame.isImportant()))
		{
			mFrame = frame;
		}
	}
}

void ImGuiProfiler::pause()
{
	mPaused = true;
}

void ImGuiProfiler::play()
{
	mPaused = false;
}

void ImGuiProfiler::draw()
{
	OE_PROFILE_FUNCTION("ImGuiProfiler::draw");

	if (isVisible())
	{
		ImGuiWindow::Begin(320, 10, 500, 300);

		if (!mPaused && ImGui::Button("Pause"))
		{
			mPaused = true;
		}
		else if (mPaused && ImGui::Button("Play"))
		{
			mPaused = false;
		}
		ImGui::SameLine();
		if (!mImportant && ImGui::Button("Important frames"))
		{
			mImportant = true;
		}
		else if (mImportant && ImGui::Button("All frames"))
		{
			mImportant = false;
		}

		ImGui::Text(std::string("Frame " + toString(mFrame.getFrameNumber()) + ", duration : " + toString(mFrame.getDuration().asMicroseconds()) + "us").c_str());

		ImGui::BeginChild("Scrolling", ImVec2(0, -ImGui::GetItemsLineHeightWithSpacing()), true, ImGuiWindowFlags_HorizontalScrollbar);
		ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(4, 1)); // Tighten spacing

		const std::vector<ProfilerFunctionCall>& calls(mFrame.getCalls());
		for (U32 i = 0; i < calls.size(); i++)
		{
			if (calls[i].getLevel() == 0)
			{
				drawFunctionCall(calls[i]);
			}
		}

		ImGui::PopStyleVar();
		ImGui::EndChild();

		ImGui::End();
	}
}

void ImGuiProfiler::drawFunctionCall(const ProfilerFunctionCall& fc)
{
	const std::vector<ProfilerFunctionCall>& calls(mFrame.getCalls());

	std::string str = fc.getName() + ", duration : " + toString(fc.getDuration().asMicroseconds()) + "us, percent : " + toString(fc.getPercent(mFrame.getDuration()));

	if (fc.hasChildren())
	{
		if (ImGui::TreeNode(str.c_str()))
		{
			for (U32 i = 0; i < calls.size(); i++)
			{
				if (calls[i].getParent() == fc.getId())
				{
					drawFunctionCall(calls[i]);
				}
			}
			ImGui::TreePop();
		}
	}
	else
	{
		if (ImGui::TreeNode(str.c_str()))
		{
			ImGui::TreePop();
		}
	}
}

ImGuiDataViewer::ImGuiDataViewer(F32 x, F32 y, F32 w, F32 h)
	: ImGuiWindow("DataViewer", x, y, w, h)
	, DataViewer()
{
}

ImGuiDataViewer::~ImGuiDataViewer()
{
	if (isConnected())
	{
		disconnect();
	}
}

void ImGuiDataViewer::setData(const std::string& key, const std::string& value)
{
	bool found = false;
	for (Data& d : mData)
	{
		if (d.key == key)
		{
			d.value = value;
			found = true;
		}
	}
	if (!found)
	{
		mData.emplace_back(key, value);
	}
}

void ImGuiDataViewer::eraseData(const std::string& key)
{
	for (auto itr = mData.begin(); itr != mData.end();)
	{
		if ((*itr).key == key)
		{
			itr = mData.erase(itr);
		}
		else
		{
			++itr;
		}
	}
}

void ImGuiDataViewer::clear()
{
	mData.clear();
}

void ImGuiDataViewer::draw()
{
	if (isVisible())
	{
		ImGuiWindow::Begin(320, 320, 200, 240);

		for (const Data& data : mData)
		{
			ImGui::Text(std::string(data.key + " : " + data.value).c_str());
		}

		ImGui::End();
	}
}

} // namespace oe
