#include <Game.h>

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
	std::srand(time(nullptr));
}

Game::~Game() {}

void Game::run()
{
	initialize();
	Event event;
	while (isRunning) {

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}
}

typedef struct
{
	float coordinate[3];
	float color[3];
} Vert;

Vert vertex[36];
Vert finalVertex[36];
MyVector3 trans = { 0,0,1 };
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	// Set cube's triangle's vertices
	setupPoints();

	// Color
	for (int i = 0; i < 36; i++)
	{
		vertex[i].color[0] = (rand() % 11) / 10.0f;
		vertex[i].color[1] = (rand() % 11) / 10.0f;
		vertex[i].color[2] = (rand() % 11) / 10.0f;
	}

	// Index
	for (int i = 0; i < 36; i++)
	{
		triangles[i] = i;
	}

	// Final position = start(with rotatation and scale) + translation
	for (int i = 0; i < 36; i++)
	{
		finalVertex[i] = vertex[i];
		finalVertex[i].coordinate[0] += trans.x;
		finalVertex[i].coordinate[1] += trans.y;
	}
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, finalVertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	// Rotate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };// Temp vector to use matrix
			tempVec = (MyMatrix3::rotationZ(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;		// Reassign to vertices
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };// Temp vector to use matrix
			tempVec = (MyMatrix3::rotationX(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;		// Reassign to vertices
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };// Temp vector to use matrix
			tempVec = (MyMatrix3::rotationY(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;	// Reassign to vertices
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;
		}
	}
	// Scale
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };	// Temp vector to use matrix
			tempVec = (MyMatrix3::scale(0.998) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;		// Reassign to vertices
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 36; i++)
		{
			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1], vertex[i].coordinate[2] };			// Temp vector to use matrix
			tempVec = (MyMatrix3::scale(1.002) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;		// Reassign to vertices
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;
		}
	}
	// Translate
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		trans = (MyMatrix3::translation(MyVector3{ 0, 0.001 ,0 }) *  trans);	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		trans = (MyMatrix3::translation(MyVector3{ 0, -0.001 ,0 }) *  trans);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		trans = (MyMatrix3::translation(MyVector3{0.001, 0 ,0 }) *  trans);	
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		trans = (MyMatrix3::translation(MyVector3{ -0.001, 0 ,0 }) *  trans);
	}
	// Update the overall translation
	for (int i = 0; i < 36; i++)
	{
		finalVertex[i] = vertex[i];			// Give color and rotate/scale
		finalVertex[i].coordinate[0] += trans.x;	// Add XnY of translation
		finalVertex[i].coordinate[1] += trans.y;
	}
}

void Game::render()
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, finalVertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glColorPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 36);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model compoents that are and are not to be drawn )	*/
	glVertexPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 0);
	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	window.display();
}

void Game::unload()
{
	cout << "Cleaning up" << endl;

	glDeleteBuffers(1, vbo);
}

void Game::setupPoints()
{

	// Back
	vertex[0].coordinate[0] = 0.5;
	vertex[0].coordinate[1] = 0.5;
	vertex[0].coordinate[2] = -0.5;

	vertex[1].coordinate[0] = -0.5;
	vertex[1].coordinate[1] = 0.5;
	vertex[1].coordinate[2] = -0.5;

	vertex[2].coordinate[0] = -0.5;
	vertex[2].coordinate[1] = -0.5;
	vertex[2].coordinate[2] = -0.5;

	vertex[3].coordinate[0] = -0.5;
	vertex[3].coordinate[1] = -0.5;
	vertex[3].coordinate[2] = -0.5;

	vertex[4].coordinate[0] = 0.5;
	vertex[4].coordinate[1] = -0.5;
	vertex[4].coordinate[2] = -0.5;

	vertex[5].coordinate[0] = 0.5;
	vertex[5].coordinate[1] = 0.5;
	vertex[5].coordinate[2] = -0.5;

	// side 1
	vertex[6].coordinate[0] = 0.5;
	vertex[6].coordinate[1] = 0.5;
	vertex[6].coordinate[2] = -0.5;

	vertex[7].coordinate[0] = 0.5;
	vertex[7].coordinate[1] = 0.5;
	vertex[7].coordinate[2] = 0.5;

	vertex[8].coordinate[0] = 0.5;
	vertex[8].coordinate[1] = -0.5;
	vertex[8].coordinate[2] = 0.5;

	vertex[9].coordinate[0] = 0.5;
	vertex[9].coordinate[1] = -0.5;
	vertex[9].coordinate[2] = 0.5;

	vertex[10].coordinate[0] = 0.5;
	vertex[10].coordinate[1] = -0.5;
	vertex[10].coordinate[2] = -0.5;

	vertex[11].coordinate[0] = 0.5;
	vertex[11].coordinate[1] = 0.5;
	vertex[11].coordinate[2] = -0.5;

	// side 2
	vertex[12].coordinate[0] = -0.5;
	vertex[12].coordinate[1] = 0.5;
	vertex[12].coordinate[2] = -0.5;

	vertex[13].coordinate[0] = -0.5;
	vertex[13].coordinate[1] = 0.5;
	vertex[13].coordinate[2] = 0.5;

	vertex[14].coordinate[0] = -0.5;
	vertex[14].coordinate[1] = -0.5;
	vertex[14].coordinate[2] = 0.5;

	vertex[15].coordinate[0] = -0.5;
	vertex[15].coordinate[1] = -0.5;
	vertex[15].coordinate[2] = 0.5;

	vertex[16].coordinate[0] = -0.5;
	vertex[16].coordinate[1] = -0.5;
	vertex[16].coordinate[2] = -0.5;

	vertex[17].coordinate[0] = -0.5;
	vertex[17].coordinate[1] = 0.5;
	vertex[17].coordinate[2] = -0.5;

	// front
	vertex[18].coordinate[0] = -0.5;
	vertex[18].coordinate[1] = 0.5;
	vertex[18].coordinate[2] = 0.5;

	vertex[19].coordinate[0] = 0.5;
	vertex[19].coordinate[1] = 0.5;
	vertex[19].coordinate[2] = 0.5;

	vertex[20].coordinate[0] = -0.5;
	vertex[20].coordinate[1] = -0.5;
	vertex[20].coordinate[2] = 0.5;

	vertex[21].coordinate[0] = -0.5;
	vertex[21].coordinate[1] = -0.5;
	vertex[21].coordinate[2] = 0.5;

	vertex[22].coordinate[0] = 0.5;
	vertex[22].coordinate[1] = -0.5;
	vertex[22].coordinate[2] = 0.5;

	vertex[23].coordinate[0] = 0.5;
	vertex[23].coordinate[1] = 0.5;
	vertex[23].coordinate[2] = 0.5;

	// bottom
	vertex[24].coordinate[0] = -0.5;
	vertex[24].coordinate[1] = -0.5;
	vertex[24].coordinate[2] = -0.5;

	vertex[25].coordinate[0] = 0.5;
	vertex[25].coordinate[1] = -0.5;
	vertex[25].coordinate[2] = -0.5;

	vertex[26].coordinate[0] = 0.5;
	vertex[26].coordinate[1] = -0.5;
	vertex[26].coordinate[2] = 0.5;

	vertex[27].coordinate[0] = 0.5;
	vertex[27].coordinate[1] = -0.5;
	vertex[27].coordinate[2] = 0.5;

	vertex[28].coordinate[0] = -0.5;
	vertex[28].coordinate[1] = -0.5;
	vertex[28].coordinate[2] = 0.5;

	vertex[29].coordinate[0] = -0.5;
	vertex[29].coordinate[1] = -0.5;
	vertex[29].coordinate[2] = -0.5;

	// Top
	vertex[30].coordinate[0] = -0.5;
	vertex[30].coordinate[1] = 0.5;
	vertex[30].coordinate[2] = -0.5;

	vertex[31].coordinate[0] = 0.5;
	vertex[31].coordinate[1] = 0.5;
	vertex[31].coordinate[2] = -0.5;

	vertex[32].coordinate[0] = 0.5;
	vertex[32].coordinate[1] = 0.5;
	vertex[32].coordinate[2] = 0.5;

	vertex[33].coordinate[0] = 0.5;
	vertex[33].coordinate[1] = 0.5;
	vertex[33].coordinate[2] = 0.5;

	vertex[34].coordinate[0] = -0.5;
	vertex[34].coordinate[1] = 0.5;
	vertex[34].coordinate[2] = 0.5;

	vertex[35].coordinate[0] = -0.5;
	vertex[35].coordinate[1] = 0.5;
	vertex[35].coordinate[2] = -0.5;
}

