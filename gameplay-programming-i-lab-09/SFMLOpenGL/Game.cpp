#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube VBO")
{
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
Vert translateVert;
GLubyte triangles[36];

/* Variable to hold the VBO identifier */
GLuint vbo[1];
GLuint index;

void Game::initialize()
{
	isRunning = true;

	glewInit();

	translateVert.coordinate[0] = 1.0f;
	translateVert.coordinate[1] = 1.0f;
	translateVert.coordinate[2] = 1.0f;
	/* Vertices counter-clockwise winding */

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



	// added side 1
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

	// Back
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

	// Color
	vertex[0].color[0] = 0.1f;
	vertex[0].color[1] = 1.0f;
	vertex[0].color[2] = 0.0f;

	vertex[1].color[0] = 0.2f;
	vertex[1].color[1] = 1.0f;
	vertex[1].color[2] = 0.0f;

	vertex[2].color[0] = 0.3f;
	vertex[2].color[1] = 1.0f;
	vertex[2].color[2] = 0.0f;

	vertex[3].color[0] = 0.4f;
	vertex[3].color[1] = 1.0f;
	vertex[3].color[2] = 0.0f;

	vertex[4].color[0] = 0.5f;
	vertex[4].color[1] = 1.0f;
	vertex[4].color[2] = 0.0f;

	vertex[5].color[0] = 0.6f;
	vertex[5].color[1] = 1.0f;
	vertex[5].color[2] = 0.0f;

	// added
	vertex[6].color[0] = 0.6f;
	vertex[6].color[1] = 0.6f;
	vertex[6].color[2] = 1.0f;

	vertex[7].color[0] = 0.6f;
	vertex[7].color[1] = 0.6f;
	vertex[7].color[2] = 1.0f;

	vertex[8].color[0] = 0.6f;
	vertex[8].color[1] = 0.6f;
	vertex[8].color[2] = 1.0f;

	vertex[9].color[0] = 1.0f;
	vertex[9].color[1] = 0.6f;
	vertex[9].color[2] = 0.6f;

	vertex[10].color[0] = 1.0f;
	vertex[10].color[1] = 0.6f;
	vertex[10].color[2] = 0.6f;

	vertex[11].color[0] = 1.0f;
	vertex[11].color[1] = 0.6f;
	vertex[11].color[2] = 0.6f;

	// moar

	vertex[12].color[0] = 1.0f;
	vertex[12].color[1] = 1.0f;
	vertex[12].color[2] = 0.0f;

	vertex[13].color[0] = 1.0f;
	vertex[13].color[1] = 1.0f;
	vertex[13].color[2] = 0.0f;

	vertex[14].color[0] = 1.0f;
	vertex[14].color[1] = 1.0f;
	vertex[14].color[2] = 0.0f;

	vertex[15].color[0] = 0.0f;
	vertex[15].color[1] = 1.0f;
	vertex[15].color[2] = 1.0f;

	vertex[16].color[0] = 0.0f;
	vertex[16].color[1] = 1.0f;
	vertex[16].color[2] = 1.0f;

	vertex[17].color[0] = 0.0f;
	vertex[17].color[1] = 1.0f;
	vertex[17].color[2] = 1.0f;

	// moar

	vertex[18].color[0] = 1.0f;
	vertex[18].color[1] = 0.0f;
	vertex[18].color[2] = 0.0f;

	vertex[19].color[0] = 1.0f;
	vertex[19].color[1] = 0.0f;
	vertex[19].color[2] = 0.0f;

	vertex[20].color[0] = 1.0f;
	vertex[20].color[1] = 0.0f;
	vertex[20].color[2] = 0.0f;

	vertex[21].color[0] = 0.0f;
	vertex[21].color[1] = 0.0f;
	vertex[21].color[2] = 1.0f;

	vertex[22].color[0] = 0.0f;
	vertex[22].color[1] = 0.0f;
	vertex[22].color[2] = 1.0f;

	vertex[23].color[0] = 0.0f;
	vertex[23].color[1] = 0.0f;
	vertex[23].color[2] = 1.0f;

	// moar

	vertex[24].color[0] = 1.0f;
	vertex[24].color[1] = 0.0f;
	vertex[24].color[2] = 1.0f;

	vertex[25].color[0] = 1.0f;
	vertex[25].color[1] = 0.0f;
	vertex[25].color[2] = 1.0f;

	vertex[26].color[0] = 1.0f;
	vertex[26].color[1] = 0.0f;
	vertex[26].color[2] = 1.0f;

	vertex[27].color[0] = 0.6f;
	vertex[27].color[1] = 1.0f;
	vertex[27].color[2] = 0.6f;

	vertex[28].color[0] = 0.6f;
	vertex[28].color[1] = 1.0f;
	vertex[28].color[2] = 0.6f;

	vertex[29].color[0] = 0.6f;
	vertex[29].color[1] = 1.0f;
	vertex[29].color[2] = 0.6f;

	// moar

	vertex[30].color[0] = 0.7f;
	vertex[30].color[1] = 0.0f;
	vertex[30].color[2] = 0.3f;

	vertex[31].color[0] = 0.7f;
	vertex[31].color[1] = 0.0f;
	vertex[31].color[2] = 0.3f;

	vertex[32].color[0] = 0.7f;
	vertex[32].color[1] = 0.0f;
	vertex[32].color[2] = 0.3f;

	vertex[33].color[0] = 0.3f;
	vertex[33].color[1] = 0.0f;
	vertex[33].color[2] = 0.7f;

	vertex[34].color[0] = 0.3f;
	vertex[34].color[1] = 0.0f;
	vertex[34].color[2] = 0.7f;

	vertex[35].color[0] = 0.3f;
	vertex[35].color[1] = 0.0f;
	vertex[35].color[2] = 0.7f;

	for (int i = 0; i < 36; i++)
	{
		triangles[i] = i;
	}

	for (int i = 0; i < 36; i++)
	{
		finalVertex[i].coordinate[0] = vertex[i].coordinate[0] + translateVert.coordinate[0];
		finalVertex[i].coordinate[1] = vertex[i].coordinate[1] + translateVert.coordinate[1];
		finalVertex[i].coordinate[2] = vertex[i].coordinate[2] + translateVert.coordinate[2];
		finalVertex[i].color[0] = vertex[i].color[0];
		finalVertex[i].color[1] = vertex[i].color[1];
		finalVertex[i].color[2] = vertex[i].color[2];
	}
	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 36, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
	{
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };

			tempVec = (MyMatrix3::rotationZ(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };

			tempVec = (MyMatrix3::rotationX(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::C))
	{
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };

			tempVec = (MyMatrix3::rotationY(0.004) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };

			tempVec = (MyMatrix3::scale(0.998) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;

		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		for (int i = 0; i < 36; i++)
		{

			MyVector3 tempVec = { vertex[i].coordinate[0], vertex[i].coordinate[1],  vertex[i].coordinate[2] };

			tempVec = (MyMatrix3::scale(1.002) * tempVec);

			vertex[i].coordinate[0] = tempVec.x;
			vertex[i].coordinate[1] = tempVec.y;
			vertex[i].coordinate[2] = tempVec.z;

		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (translateVert.coordinate[2] >= 0)
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0, 0.001 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
		else
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0, -0.001 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (translateVert.coordinate[2] >= 0)
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0, -0.001 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
		else
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0, 0.001 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (translateVert.coordinate[2] >= 0)
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0.001, 0 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
		else
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ -0.001, 0 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (translateVert.coordinate[2] >= 0)
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ -0.001, 0 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
		else
		{
			MyVector3 dis = { translateVert.coordinate[0], translateVert.coordinate[1], translateVert.coordinate[2] };
			dis = (MyMatrix3::translation(MyVector3{ 0.001, 0 ,0 }) *  dis);			// Rotate them all
			translateVert.coordinate[0] = dis.x;
			translateVert.coordinate[1] = dis.y;
			translateVert.coordinate[2] = dis.z;
		}
	}


	for (int i = 0; i < 36; i++)
	{
		finalVertex[i].coordinate[0] = vertex[i].coordinate[0] + translateVert.coordinate[0];
		finalVertex[i].coordinate[1] = vertex[i].coordinate[1] + translateVert.coordinate[1];
		finalVertex[i].coordinate[2] = vertex[i].coordinate[2] + translateVert.coordinate[2];
		finalVertex[i].color[0] = vertex[i].color[0];
		finalVertex[i].color[1] = vertex[i].color[1];
		finalVertex[i].color[2] = vertex[i].color[2];
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
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * 36, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glLoadIdentity();
	glTranslatef(0, 0, 0);

	glColorPointer(3, GL_FLOAT, sizeof(Vert), (char*)NULL + 12);

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

