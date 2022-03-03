#include"imgui.h"
#include"imgui_impl_glfw.h"
#include"imgui_impl_opengl3.h"
#include <ctime>
#include<iostream>
#include<glad/glad.h>
#include <windows.h>
#include <sstream>
#include<GLFW/glfw3.h>
#include <string>
#define LEAN_AND_MEAN
#define STB_IMAGE_IMPLEMENTATION

void dclock(char buffer[], ImGuiWindowFlags winflag);
void fpscount(float fps, ImGuiWindowFlags winflag);
void test();
void changevolume(int sliderin);
void settings();

typedef struct {
	bool settingser;
	int sliderint;
} Foo;
static float slidernum = 500.0f;
static float slidernum2 = 200.0f;

int main()
{
	
	// Initialize GLFW
	glfwInit();
	ImGuiWindowFlags window_flags = 0
		| ImGuiWindowFlags_NoTitleBar
		| ImGuiWindowFlags_NoResize
		| ImGuiWindowFlags_NoMove
		| ImGuiWindowFlags_NoScrollbar
		| ImGuiWindowFlags_NoSavedSettings
		;
	// Tell GLFW what version of OpenGL we are using 
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Koros app ", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		delete window;
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);
	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, 800, 800);
	static bool bscalar = false;
	static bool show = false;
	static bool gotogit = false;
	static bool settingser = false;
	// Initialize ImGUI
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");

	// Variables to be changed in the ImGUI window
	static bool isClicked = false;
	std::unique_ptr<Foo> foo(new Foo);
	foo->settingser = false;
	while (!glfwWindowShouldClose(window)){
		float fps = ImGui::GetIO().Framerate;
		time_t now = time(0);
		char buf[26];
		// convert now to string form
		ctime_s(buf,26,&now);
		// Specify the color of the background
		glClearColor(0.0f / 255.0f, 224.0f / 255.0f, 255.0f / 255.0f, 1.0f);
		// Clean the back buffer and assign the new color to it
		glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL a new frame is about to begin
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();


		float ImGuiWidth = slidernum;
		float ImGuiHight = slidernum2;


		// ImGUI window creation
		dclock(buf, window_flags);
		fpscount(fps, window_flags);
		ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(200.0f / 255.0f, 235.0f / 255.0f, 211.0f / 255.0f, 1.0f));
		ImGui::Begin("my name is window, imgui window");
		ImGui::PopStyleColor();
		ImGui::SetWindowSize(ImVec2(ImGuiWidth, ImGuiHight));
		static float weight = 0;
		static float height = 0;
		ImGui::InputFloat("hello", &weight, 0, 0, 0);
		ImGui::InputFloat("gello", &height, 0, 0, 0);
		//to change volume?system(combined.c_str());
		if (ImGui::BeginMenu("Examples"))
		{
			ImGui::MenuItem("Button basically", NULL, &show);
			ImGui::MenuItem("Give me git", NULL, &gotogit);
			ImGui::MenuItem("Settings", NULL, &foo->settingser);
			ImGui::EndMenu();
		}

		if (show == true) {
			
			if (height == 0 || weight == 0){
				std::cout << height << weight << std::endl;
				ImGui::Text("ENTER A VALID VALUE");
			}
			else {
				static float realheight = height / 100;
				realheight * height;
				ImGui::Text("%f", weight / realheight );
			}
		}
		if (gotogit == true) {
			system("START https://github.com/KoroLikesMelon");
			gotogit = false;
		}
		if (foo->settingser == true) {
			settings();
			isClicked = true;
			
		}
		if (isClicked) {
			isClicked = false;
		}


		
		
		// Text that appears in the window

		if (ImGui::Button("Button")) {
			
		}
		

	
		// Checkbox that appears in the windo
		// Ends the window
		ImGui::End();	
		// Export variables to shader
		// Renders the ImGUI elements
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}
	// Deletes all ImGUI instances
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	// Delete all the objects we've created
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}
void dclock(char buffer[], ImGuiWindowFlags winflag) {
	ImGui::SetNextWindowPos(ImVec2(620.0f, 570.0f));
	ImGui::SetNextWindowSize(ImVec2(180.0f, 3.0f));
	ImGui::Begin("Digital Clock", NULL, winflag);
	ImGui::Text(buffer);
	ImGui::End();
}
void fpscount(float fps, ImGuiWindowFlags winflag) {
	ImGui::SetNextWindowPos(ImVec2(3.0f, 3.0f));
	ImGui::SetNextWindowSize(ImVec2(180.0f, 3.0f));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0 / 255.0f, 224.0 / 255.0f, 255.0 / 255.0f, 1.0f));
	ImGui::Begin("Dasd", NULL, winflag);
	ImGui::PopStyleColor();
	ImGui::PopStyleVar();
	ImGui::PushStyleColor(ImGuiCol_Text, IM_COL32(0, 0, 0, 255));
	ImGui::Text("%f", fps);
	ImGui::PopStyleColor();
	ImGui::End();
}
void settings() {
	ImGui::SetNextWindowSize(ImVec2(200.f, 200.f));
	ImGui::Begin("Test WIndow", NULL, NULL);	
	ImGui::SliderFloat("ye", &slidernum, 500.f, 800.f);
	ImGui::SliderFloat("asd", &slidernum2, 500.f, 600.f);
	ImGui::End();
	
}
void changevolume(int sliderint) {
	std::stringstream ss;
	ss << sliderint;
	std::string stringvolume;
	ss >> stringvolume;
	std::string combined = "setvol " + stringvolume;
}
void asd() {
	static float slidernum;
	static int sliderint = 25;

	//ImGui::SetNextWindowPos(ImVec2(250.0f, 250.0f));
	///ImGui::SetNextWindowSize(ImVec2(300.0f, 300.0f));
	//ImGui::Begin("Dasd", NULL, ImGuiWindowFlags_AlwaysVerticalScrollbar);

	//ImGui::SliderFloat("ye", &slidernum, 100.f, 500.f);
	//ImGui::SliderInt("volume", &sliderint, 0, 100);
	//ImGui::End();
	
}