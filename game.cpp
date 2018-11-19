#include "game.h"
#include "resource_manager.h"
#include "sprite_renderer.h"
#include <iostream>

SpriteRenderer *Renderer;

Game::Game(GLuint width, GLuint height)
  : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
  delete Renderer;
}


void Game::Init() {
  // Load shaders
  ResourceManager::LoadShader("shaders/sprite.vs", "shaders/sprite.frag", nullptr, "sprite");

  // Configure shaders
  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  ResourceManager::GetShader("sprite").Use().SetInteger("sprite", 0);
  ResourceManager::GetShader("sprite").SetMatrix4("projection", projection);

  // Load textures
  ResourceManager::LoadTexture("textures/background.jpg", GL_FALSE, "background");
  ResourceManager::LoadTexture("textures/awesomeface.png", GL_FALSE, "face");
  ResourceManager::LoadTexture("textures/block.png", GL_FALSE, "block");
  ResourceManager::LoadTexture("textures/block_solid.png", GL_FALSE, "block_solid");

  // Set render-specific controls
  Shader myShader;
  myShader = ResourceManager::GetShader("sprite");
  Renderer = new SpriteRenderer(myShader);
  //Renderer = new SpriteRenderer(ResourceManager::GetShader("sprite"));

  // Load levels
  GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height * 0.5);
  GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height * 0.5);
  GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height * 0.5);
  GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height * 0.5);
  this->Levels.push_back(one);
  this->Levels.push_back(two);
  this->Levels.push_back(three);
  this->Levels.push_back(four);
  this->Level = 0;
}

void Game::Update(GLfloat dt) {

}

void Game::ProcessInput(GLfloat dt) {

}

void Game::Render() {
  //Texture2D myTexture;
  //myTexture = ResourceManager::GetTexture("background");
  //Renderer->DrawSprite(myTexture, glm::vec2(200, 200), glm::vec2(300, 400), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));

  if (this->State == GAME_ACTIVE) {
    // Draw background
    Texture2D myBackground;
    myBackground = ResourceManager::GetTexture("background");
    Renderer -> DrawSprite(myBackground, glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f);
    //Renderer->DrawSprite(ResourceManager::GetTexture("background"), glm::vec2(0, 0), glm::vec2(this->Width, this->Height), 0.0f)

    // Draw level
    this->Levels[this->Level].Draw(*Renderer);
  }
}
