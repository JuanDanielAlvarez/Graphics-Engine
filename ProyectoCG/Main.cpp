#include"Model.h"


const unsigned int width = 800;
const unsigned int height = 800;


int main()
{
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	gladLoadGL();
	glViewport(0, 0, width, height);




	Shader shaderProgram("default.vert", "default.frag");

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(0.5f, 0.5f, 0.5f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

	shaderProgram.Activate();
	glUniform4f(glGetUniformLocation(shaderProgram.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(shaderProgram.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);


	glEnable(GL_DEPTH_TEST);

	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));

	std::string modelPath = "Resources/space_exploration_wlp_series_8/scene.gltf";

	Model model((modelPath).c_str());

	std::string modelPath2 = "Resources/satelite/scene.gltf";
	Model model2((modelPath2).c_str());

	std::string modelPath3 = "Resources/3december_2021_day_18_astronaut/scene.gltf";
	Model model3((modelPath3).c_str());


	float angle = glfwGetTime();

	while (!glfwWindowShouldClose(window))
	{
		angle = glfwGetTime();

		float posX = sin(angle) * 20;
		float posY = cos(angle) * 20;

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		camera.Inputs(window);
		camera.updateMatrix(0.1f, 1000.0f);

		model.Draw(shaderProgram, camera, glm::vec3(0.0f,0.0f,0.0f), glm::vec3(angle, -2.5f, 0.0f), 0.5f);

		model2.Draw(shaderProgram, camera, glm::vec3(0.0f, posY, posX), glm::vec3(angle, -2.5f, 0.0f) , 0.2f);

		model3.Draw(shaderProgram, camera, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(angle, -2.5f, 0.0f), 1.0f);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}



	shaderProgram.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}