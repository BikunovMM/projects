#include "Game.hpp"

/*
================================

Game::Object
	wraps object(model)
	and it's data

================================
*/

/*
===============

Game::Object::Object(...)
	Main Object's constructor with parameters

===============
*/

Game::Object::Object(unsigned int 		 model_mat_id,
					 unsigned int        vbo,
	 		         const char *const   tex0_path,
			         const char *const   tex1_path,
					 const char *const   tex2_path,
			         const unsigned int *indicies,
			         int                 verticies_len,
			         bool                has_normals,
			         glm::vec3          *pos,
					 glm::vec3			*rotation,
					 float				 rotation_angle,
					 glm::vec3			*scale,
			         const float         shin)
	: TEXTURE_PATHS{nullptr, nullptr, nullptr},
	  model_mat_id(model_mat_id),
	  vao(0),	  
	  vbo(vbo),	  
	  ebo(0),
	  verticies_len(verticies_len),	 
	  textures{0, 0, 0},
	  model_mat(1.0f),
	  position(*pos),
	  rotation(*rotation),
	  rotation_angle(rotation_angle),
	  scale(*scale),
	  shininess(shin),
	  has_normals(has_normals),
	  shares_data(false)
{
	if (!tex0_path || !tex1_path || !indicies) {
		fprintf(stderr, "Wrong Object::Object(...) argiments were given.\n");
		return;
	}

	//	TEXTURE_PATHS
	//
	TEXTURE_PATHS[0] = (char*)std::malloc(sizeof(char) * std::strlen(tex0_path) + 1);
	if (!TEXTURE_PATHS[0]) {
		fprintf(stderr, "Failed to malloc TEXTURE_PATHS[0].\n");
		return;
	}

	std::strcpy(TEXTURE_PATHS[0], tex0_path);
	if (!TEXTURE_PATHS[0]) {
		fprintf(stderr, "Failed to strcpy TEXTURE_PATHS[0].\n");
		return;
	}

	if (tex1_path) {
		TEXTURE_PATHS[1] = (char*)std::malloc(sizeof(char) * std::strlen(tex1_path) + 1);
		if (!TEXTURE_PATHS[1]) {
			fprintf(stderr, "Failed to malloc TEXTURE_PATHS[1].\n");
			return;
		}

		std::strcpy(TEXTURE_PATHS[1], tex1_path);
		if (!TEXTURE_PATHS[1]) {
			fprintf(stderr, "Failed to stdcpy TEXTURE_PATHS[1].\n");
			return;
		}
	}
	if (tex2_path) {
		TEXTURE_PATHS[2] = (char*)std::malloc(sizeof(char) * std::strlen(tex2_path) + 1);
		if (!TEXTURE_PATHS[2]) {
			fprintf(stderr, "Failed to malloc TEXTURE_PATHS[2].\n");
			return;
		}

		std::strcpy(TEXTURE_PATHS[2], tex2_path);
		if (!TEXTURE_PATHS[2]) {
			fprintf(stderr, "Failed to stdcpy TEXTURE_PATHS[2].\n");
			return;
		}
	}


	//	indicies
	//
	this->indicies = 
		(unsigned int*)std::malloc(sizeof(unsigned int) * this->verticies_len);
	if (!this->indicies) {
		fprintf(stderr, "Failed malloc indicies in "
			"Object::Object(...).\n");
		return;
	}

	std::memcpy(this->indicies, indicies, 
		this->verticies_len * sizeof(unsigned int));
	
	puts("\nconstructor(...)");
	fflush(stdout);
}

/*
===============

Game::Object::Object(void)
	Parameterless Object's constructor

===============
*/

Game::Object::Object(void)
	: TEXTURE_PATHS{nullptr, nullptr, nullptr},
	  model_mat_id(0),
	  vao(0),	  
	  vbo(0),	  
	  ebo(0),
	  indicies(nullptr),
	  verticies_len(0),
	  textures{0, 0, 0},
	  model_mat(1.0f),
	  position(0.0f),
	  rotation(0.0f),
	  rotation_angle(0.0f),
	  scale(1.0f),
	  shininess(16.0f),
	  has_normals(true),
	  shares_data(false)
{	
	puts("constructor(void)");
	fflush(stdout);
}

/*
===============

Game::Object::~Object(void)
	Object's destructor
	frees all malloced Object's data

===============
*/

Game::Object::~Object(void)
{
	printf("destructor:\n\ttex0_path: %s;\n", TEXTURE_PATHS[0]);
	fflush(stdout);

	if (!shares_data) {
		if (indicies) {
			std::free(indicies);
			printf("\tindicies are freed %d.\n", __LINE__);
			fflush(stdout);
		}
		if (TEXTURE_PATHS[0]) {
			std::free(TEXTURE_PATHS[0]);
			printf("\tTEXTURE_PATHS[0] is freed %d.\n", __LINE__);
			fflush(stdout);
		}
		if (TEXTURE_PATHS[1]) {
			std::free(TEXTURE_PATHS[1]);
			printf("\tTEXTURE_PATHS[1] is freed %d.\n", __LINE__);
			fflush(stdout);
		}
		if (TEXTURE_PATHS[2]) {
			std::free(TEXTURE_PATHS[2]);
			printf("\tTEXTURE_PATHS[2] is freed %d.\n", __LINE__);
			fflush(stdout);
		}
	}
	putchar('\n');

	if (textures[2]) {
		glDeleteTextures(3, textures);
	}
	else if (textures[1]) {
		glDeleteTextures(2, textures);
	}
	else {
		glDeleteTextures(1, textures);
	}

	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
}

/*
===============

Game::Object::is_vald(...)
	return is Object valid

===============
*/

bool Game::Object::is_valid(void) const{
	return (vbo && vao && ebo);
}

/*
===============

Game::Object::~get_model_mat_id(void)
	returns Object's model_mat_id

===============
*/

unsigned int Game::Object::get_model_mat_id(void) const {
	return model_mat_id;
}

/*
===============

Game::Object::get_vao(void)
	returns Object::vao value

===============
*/

unsigned int Game::Object::get_vao(void) const {
	return vao;
}

/*
===============

Game::Object::get_vbo(void)
	returns Object::vbo value

===============
*/

unsigned int Game::Object::get_vbo(void) const {
	return vbo;
}

/*
===============

Game::Object::get_ebo(void)
	returns Object::ebo value

===============
*/

unsigned int Game::Object::get_ebo(void) const {
	return ebo;
}		

/*
===============

Game::Object::get_verticies_len(void)
	returns Object::verticies_len value

===============
*/

unsigned int Game::Object::get_verticies_len(void) const {
	return verticies_len;
}

/*
===============

Game::Object::get_model_mat(void)
	returns Object::model_mat value

===============
*/

glm::mat4 Game::Object::get_model_mat(void) const {
	return model_mat;
}

/*
===============

Game::Object::get_position(void)
	returns Object::position value

===============
*/

glm::vec3 Game::Object::get_position() const {
	return position;
}

/*
===============

Game::Object::get_rotation_angle(void)
	returns Object::rotation_angle value

===============
*/

float Game::Object::get_rotation_angle() const {
	return rotation_angle;
}

/*
===============

Game::Object::get_rotation(void)
	returns Object::rotation value

===============
*/

glm::vec3 Game::Object::get_rotation() const {
	return rotation;
}

/*
===============

Game::Object::get_scale(void)
	returns Object::scale value

===============
*/

glm::vec3 Game::Object::get_scale() const {
	return scale;
}


/*
===============

Game::Object::get_shininess(void)
	returns Object::shininess value

===============
*/

const float Game::Object::get_shininess(void) const {
	return shininess;
}

/*
===============

Game::Object::get_has_normals(void)
	returns Object::has_normals value

===============
*/

const bool Game::Object::get_has_normals(void) const {
	return has_normals;
}

/*
===============

Game::Object::cpy_texture_paths(void)
	returns Object::vao value

===============
*/

void Game::Object::cpy_texture_paths(char* (new_texture_paths)[3]) const {
	new_texture_paths[0] = this->TEXTURE_PATHS[0];
	new_texture_paths[1] = this->TEXTURE_PATHS[1];
	new_texture_paths[2] = this->TEXTURE_PATHS[2];

	printf("\tcopied textures:\n\t\t%s,\n\t\t%s,\n\t\t%s.\n",
		new_texture_paths[0] ? new_texture_paths[0] : (char*)"nullptr",
		new_texture_paths[1] ? new_texture_paths[1] : (char*)"nullptr",
		new_texture_paths[2] ? new_texture_paths[2] : (char*)"nullptr");
	fflush(stdout);
	if (!(this->shares_data)){
		this->shares_data = true;
	}
}

/*
===============

Game::Object::cpy_indicies(...)
	copies pointer to allocated indicies
	from old one to new Object 

===============
*/

void Game::Object::cpy_indicies(unsigned int **new_indicies) const{
	*new_indicies = this->indicies;
	if (!this->shares_data) {
		this->shares_data = true;
	}
}

/*
===============

Game::Object::get_model_mat_ptr(...)
	copies pointer to model_mat

===============
*/

const glm::mat4 *const Game::Object::get_model_mat_ptr(void) const {
	return &model_mat;
}		

/*
===============

Game::Object::get_position_ptr(...)
	copies pointer to position

===============
*/

const glm::vec3 *const Game::Object::get_position_ptr(void) const {
	return &position;
}	

/*
===============

Game::Object::get_rotation_ptr(...)
	copies pointer to allocated rotation

===============
*/

const glm::vec3 *const Game::Object::get_rotation_ptr(void) const {
	return &rotation;
}	

/*
===============

Game::Object::get_scale_ptr(...)
	copies pointer to scale

===============
*/

const glm::vec3 *const Game::Object::get_scale_ptr(void) const {
	return &scale;
}

/*
===============

Game::Object::operator=(...)
	Object's operator= overload
	invokes on "Object obj0 = Object obj1;"

===============
*/

Game::Object& Game::Object::operator=(const Game::Object& obj) {
	printf("\toperator=;\n");

	this->model_mat_id 	   = obj.get_model_mat_id();
	this->vbo              = obj.get_vbo();					
	this->verticies_len    = obj.get_verticies_len();			
	this->model_mat 	   = obj.get_model_mat();
	this->position         = obj.get_position();
	this->rotation_angle   = obj.get_rotation_angle();
	this->rotation         = obj.get_rotation();
	this->scale            = obj.get_scale();
	this->shininess        = obj.get_shininess();
	this->has_normals      = obj.get_has_normals();// -rm

	obj.cpy_texture_paths(this->TEXTURE_PATHS);
	if (!(this->TEXTURE_PATHS[0])) {
		fprintf(stderr, "Failed to cpy_texture_paths in Object::operator=.\n");
	}

	obj.cpy_indicies(&(this->indicies));
	if (!this->indicies) {
		fprintf(stderr, "Failed to cpy_indicies in Object::operator=.\n");
	}

	fflush(stdout);

	return *this;
}

/*
===============

Game::Object::init(void)
	Initializes all object's data
	on error return negative value(-1)

===============
*/

int Game::Object::init(void)
{
	int res = 0;

	//	VertexArrays and Buffers
	//
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &ebo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * verticies_len,
		indicies, GL_STATIC_DRAW);

	if (has_normals) {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE,
			8 * sizeof(float), (void*)(void*)(sizeof(float) * 5));
		glEnableVertexAttribArray(2);
	}
	else {
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
			5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE,
			5 * sizeof(float), (void*)(sizeof(float) * 3));
		glEnableVertexAttribArray(1);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//	Textures
	//

	// Texture0 - diffuse
	if (TEXTURE_PATHS[2]) {
		puts("generated 3 textures.");
		glGenTextures(3, textures);
	}
	if (TEXTURE_PATHS[1]) {
		puts("generated 2 textures.");
		glGenTextures(2, textures);
	}
	else {
		puts("generated 1 texture.");
		glGenTextures(1, textures);
	}

	glBindTexture(GL_TEXTURE_2D, textures[0]);
	init_texture(&textures[0]);

	res = set_texture(TEXTURE_PATHS[0]);
	if (res < 0) {
		fprintf(stderr, "Failed to set_texture "
			"(texture00).\n");
		goto err;
	}

	glGenerateMipmap(GL_TEXTURE_2D);

	// Texture1 - specular
	if (TEXTURE_PATHS[1]) {
		glBindTexture(GL_TEXTURE_2D, textures[1]);
		init_texture(&textures[1]);

		res = set_texture(TEXTURE_PATHS[1]);
		if (res < 0) {
			fprintf(stderr, "Failed to set_texture "
				"(texture01).\n");
			goto err;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	// Texture1 - emission
	if (TEXTURE_PATHS[2]) {
		glBindTexture(GL_TEXTURE_2D, textures[2]);
		init_texture(&textures[2]);

		res = set_texture(TEXTURE_PATHS[2]);
		if (res < 0) {
			fprintf(stderr, "Failed to set_texture "
				"(texture02).\n");
			goto err;
		}

		glGenerateMipmap(GL_TEXTURE_2D);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	//	Transformation
	//

	translate_perform();
	rotate_perform();
	scale_perform();

	return res;

	err:
	glDeleteBuffers(1, &ebo);
	glDeleteVertexArrays(1, &vao);
	glDeleteTextures(3, textures);

	return res;
}

/*
===============

Game::Object::draw(void)
	Draws object with it textures

===============
*/

void Game::Object::draw(void)
{
	glBindVertexArray(vao);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textures[0]);

	if (textures[1]) {
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textures[1]);
	}
	if (textures[2]) {
		fflush(stdout);
		glActiveTexture(GL_TEXTURE2);
		glBindTexture(GL_TEXTURE_2D, textures[2]);
	}

	glUniformMatrix4fv(model_mat_id, 1, GL_FALSE, glm::value_ptr(model_mat));

	glDrawElements(GL_TRIANGLES, verticies_len, GL_UNSIGNED_INT, 0);

	// cleanup
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	model_mat = glm::mat4(1.0f);
}

/*
===============

Game::Object::translate_add(...)
	Adds parameter-position to this->position

===============
*/

void Game::Object::translate_add(glm::vec3 *position)
{
	if (position) {
		this->position += *position;
	}
}

/*
===============

Game::Object::translate_add(...)
	Adds parameter-position to this->position

===============
*/

void Game::Object::translate_add(glm::vec3 &&position) {
	this->position += position;
}

/*
===============

Game::Object::translate_perform(void)
	Calculates translation to the model_mat

===============
*/

void Game::Object::translate_perform(void)
{
	model_mat = glm::translate(model_mat, this->position);
}

/*
===============

Game::Object::rotate_add(...)
	Adds parameter-rotation_angle
	to this->rotation_angle, 
	parameter-rotation to this->rotation

===============
*/

void Game::Object::rotate_add(float angle, glm::vec3 *rotation)
{
	if (angle != 0.0f && rotation) {
		this->rotation_angle += angle;
		this->rotation       = *rotation;
	}
}

/*
===============

Game::Object::rotate_add(...)
	Adds parameter-rotation_angle
	to this->rotation_angle, 
	parameter-rotation to this->rotation

===============
*/

void Game::Object::rotate_add(float angle, glm::vec3 &&rotation) {
	this->rotation_angle += angle;
	this->rotation       = rotation;
}

/*
===============

Game::Object::rotate_perform(...)
	Calculates rotation to the model_mat

===============
*/

void Game::Object::rotate_perform(void)
{
	model_mat = glm::rotate(model_mat, this->rotation_angle, this->rotation);
}

/*
===============

Game::Object::scale_add(...)
	Adds parameter-scale to this->scale

===============
*/

void Game::Object::scale_add(glm::vec3 *scale)
{
	if (scale) {
		this->scale = *scale;
	}
}

/*
===============

Game::Object::scale_add(...)
	Adds parameter-scale to this->scale

===============
*/

void Game::Object::scale_add(glm::vec3 &&scale) {
	this->scale = scale;
}

/*
===============

Game::Object::scale_perform(...)
	Calculates scale to the model_mat

===============
*/

void Game::Object::scale_perform(void)
{
	model_mat = glm::scale(model_mat, this->scale);
}

/*
================
Game::Object::init_texture()
	initializes single texture,
	with the same parameters
================
*/

void Game::Object::init_texture(unsigned int *texture)
{	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

/*
================
Game::Object::set_texture()
	sets path-image to the 
	current-binded texture
================
*/

int Game::Object::set_texture(const char *const path)
{
	AVFormatContext   *ifmt_ctx    = nullptr;
	AVCodecParameters *dec_par     = nullptr;
	const AVCodec     *dec         = nullptr;
	AVCodecContext    *dec_ctx     = nullptr;
	AVPacket          *pkt         = nullptr;
	AVFrame		      *frame       = nullptr;
	unsigned char      bytes4pixel = 0;
	int   		       pix_fmt     = 0;
	int 		       res         = 0;
	
	// Init
	//
	
	res = avformat_open_input(&ifmt_ctx, path,
		nullptr, nullptr);
	if (res < 0) {
		fprintf(stderr, "Failed to "
			"avformat_open_input.\n");
		return res;
	}
	
	res = avformat_find_stream_info(ifmt_ctx, nullptr);
	if (res < 0) {
		fprintf(stderr, "Failed to "
			"avformat_find_stream_info.\n");
		goto close_input;
	}
	
	
	// Prepare to Decoding
	//
	
	dec_par = ifmt_ctx->streams[0]->codecpar;
	
	if (!dec_par) {
		fprintf(stderr, "Failed. "
			"ifmt_ctx has no codecpar.\n");
		goto close_input;
	}
	
	dec = avcodec_find_decoder(dec_par->codec_id);
	if (!dec) {
		fprintf(stderr, "Failed. "
			"dec_par has no codec_id.\n");
		goto close_input;
	}
	
	dec_ctx = avcodec_alloc_context3(dec);
	if (!dec_ctx) {
		fprintf(stderr, "Failed to "
			"avcodec_alloc_context3.\n");
		goto close_input;
	}
	avcodec_parameters_to_context(dec_ctx, dec_par);
	avcodec_open2(dec_ctx, dec, nullptr);
	
	pkt = av_packet_alloc();
	if (!pkt) {
		fprintf(stderr, "Failed to "
			"av_packet_alloc.\n");
		goto free_dec_ctx;
	}
	
	frame = av_frame_alloc();
	if (!frame) {
		fprintf(stderr, "Failed to "
			"av_frame_alloc.\n");
		goto free_pkt;
	}
	
	// Decoding
	//
	
	res = av_read_frame(ifmt_ctx, pkt);
	if (res < 0) {
		fprintf(stderr, "Failed to "
			"av_read_frame.\n");
		goto free_frame;
	}
	
	res = avcodec_send_packet(dec_ctx, pkt);
	if (res < 0) {
		fprintf(stderr, "Failed to "
			"avcodec_send_packet.\n");
		goto free_frame;
	}
	
	res = avcodec_receive_frame(dec_ctx, frame);
	if (res < 0) {
		fprintf(stderr, "Failed to "
			"avcodec_receive_frame.\n");
		goto free_frame;
	}
	
	// SettingTexture
	//
	
	if (frame->format == AV_PIX_FMT_RGB24) {
		bytes4pixel = 3;
		pix_fmt = GL_RGB;
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	}
	else if (frame->format == AV_PIX_FMT_RGBA) {
		bytes4pixel = 4;
		pix_fmt = GL_RGBA;
	}
	else {
		fprintf(stderr, "Failed. Unknown "
			"pixel format.\n");
		res = -1;
		goto free_frame;
	}
	
	glPixelStorei(GL_UNPACK_ROW_LENGTH,
		frame->linesize[0] / bytes4pixel);
	glTexImage2D(GL_TEXTURE_2D, 0, pix_fmt, frame->width,
		frame->height, 0, pix_fmt, GL_UNSIGNED_BYTE, 
		frame->data[0]);
	
	glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, 4);
	
	// Cleanup
	//
	
	free_frame:
	av_frame_free(&frame);
	free_pkt:
	av_packet_free(&pkt);
	free_dec_ctx:
	avcodec_free_context(&dec_ctx);
	close_input:
	avformat_close_input(&ifmt_ctx);
	
	return res;
}


/*
================================

Game
	main class,
	handles game and window

================================
*/

/*
===============
Game::Game()
	main parameterless constructor
===============
*/
Game::Game(int win_width, int win_height)
	: window{nullptr},
	  running(true),
	  res(0),
	  win_w(win_width), 
	  win_h(win_height),
	  win_w_centered(win_width / 2.0f), 
	  win_h_centered(win_height / 2.0f),
	  light_color{1.0f, 1.0f, 1.0f},
	  world_up(0.0f, 1.0f, 0.0f),
	  cam_pos(0.0f, 0.0f, 5.0f),
	  cam_front(0.0f, 0.0f, -1.0f),
	  cam_right(glm::normalize(glm::cross(cam_front, world_up))),
	  cam_up(glm::normalize(glm::cross(cam_right, cam_front))),
	  positions{
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, -3.0f, 0.0f),
		glm::vec3(-3.0f, -0.75f, 0.0f),
		glm::vec3(0.0f, 1.5f, 0.0f),
		glm::vec3(0.0f, -1.0f, 0.0f)//	direction_light
	  },
	  rotations {
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.1f, 0.0f, 0.0f),
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.1f, 0.0f, 0.0f)
	  },
	  scales {
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(3.0f, 1.0f, 3.0f),
		glm::vec3(0.75f, 0.75f, 0.75f),
		glm::vec3(0.5f, 0.5f, 0.5f)
	  },
	  deltatime(0.0f),
	  pyramid_move_coef(0.01f),
	  rotation(0.0f),
	  prev_tp(std::chrono::steady_clock::now()),
	  cam_trans_speed(0.1f),
	  cam_rtn_speed(0.5f),
	  key_states{nullptr},
	  relative_moded(true),
	  esc_released(true),
	  objects{Game::Object(), Game::Object(), Game::Object(), Game::Object()}
{

}

/*
===============
Game::~Game()
	main parameterless destructor
===============
*/

Game::~Game(void)
{
	glDeleteTextures(1, main_light_tex);
	puts("Game::~Game(void)\n");
	glDeleteBuffers(1, vbos);

	glDeleteProgram(light_program);
	glDeleteProgram(main_program);

	SDL_GL_DestroyContext(gl_ctx);

	SDL_DestroyWindow(window);
	SDL_Quit();
}

/*
================
Game::init()
	initialize Game data
================
*/

int Game::init(void)
{
	SDL_SetAppMetadata("SDL3_app", "2.61",
	        "ru.misha.sdl3_proj3cts");

	if (!SDL_Init(SDL_INIT_VIDEO)) {
	        fprintf(stderr, "Failed to SDL_Init. Err: %s.",
	                SDL_GetError());
	        return -1;
	}

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
		SDL_GL_CONTEXT_PROFILE_CORE);

	window = SDL_CreateWindow("pr00_SDL3", win_w, win_h,
	        SDL_WINDOW_OPENGL |  SDL_WINDOW_RESIZABLE);
	if (!window) {
	        fprintf(stderr, "Failed to SDL_CreateWindow. "
	                "Err: %s.\n",
	                SDL_GetError()
	        );
	        res = -1;
	        goto quit;
	}

	SDL_SetWindowRelativeMouseMode(window, true);
	SDL_WarpMouseInWindow(window, win_w_centered, win_h_centered);

	gl_ctx = SDL_GL_CreateContext(window);
	if (!gl_ctx) {
		fprintf(stderr, "Failed to "
			"SDL_GL_CreateContext. Err: %s.",
	                SDL_GetError()
		);
		res = -1;
		goto destroy_win;
	}

	if (!gladLoadGLLoader(
		(GLADloadproc)SDL_GL_GetProcAddress)) {
	        fprintf(stderr, "Failed to gladLoadGLLoader"
	                ".\n");
	        res = -1;
	        goto destroy_gl_ctx;
	}

	SDL_GL_MakeCurrent(window, gl_ctx);

	glEnable(GL_DEPTH_TEST);
	glViewport(0, 0, win_w, win_h);

	// OPENGL
	// ------

	// Shaders
	//

	main_program = create_program(MAIN_VS_PATH,
		MAIN_FS_PATH);
	if (!main_program) {
		fprintf(stderr, "Failed to create_program "
			"(main_program).\n");
		res = -1;
		goto delete_program;
	}

	light_program = create_program(LIGHT_VS_PATH,
		LIGHT_FS_PATH);
	if (!light_program) {
		fprintf(stderr, "Failed to create_program "
			"(light_program).\n");
		res = -1;
		goto delete_light_program;
	}

	// Verticies
	//

	glGenBuffers(1, vbos);
	glBindBuffer(GL_ARRAY_BUFFER, vbos[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTS), VERTS,
		GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Getting and passing uniforms
	//

	main_view_pos_id = glGetUniformLocation(main_program, "viewPos");
	
	main_mat_diffuse_id   = glGetUniformLocation(main_program, "mat.diffuse");
	main_mat_specular_id  = glGetUniformLocation(main_program, "mat.specular");
	main_mat_emission_id  = glGetUniformLocation(main_program, "mat.emission");
	main_mat_shininess_id = glGetUniformLocation(main_program, "mat.shininess");
	
	main_light_ambient_id  = glGetUniformLocation(main_program, "light.ambient");
	main_light_diffuse_id  = glGetUniformLocation(main_program, "light.diffuse");
	main_light_specular_id = glGetUniformLocation(main_program, "light.specular");	
	main_light_emission_id = glGetUniformLocation(main_program, "light.emission");

	main_light_position_id    = glGetUniformLocation(main_program, "light.position");
	main_light_direction_id   = glGetUniformLocation(main_program, "light.direction");
	main_light_cut_off_id     = glGetUniformLocation(main_program, "light.cutOff");
	main_light_out_cut_off_id = glGetUniformLocation(main_program, "light.outCutOff");
	
	main_light_constant_id  = glGetUniformLocation(main_program, "light.constant");
	main_light_linear_id    = glGetUniformLocation(main_program, "light.linear");
	main_light_quadratic_id = glGetUniformLocation(main_program, "light.quadratic");

	main_light_tex_id       = glGetUniformLocation(main_program, "light.tex");

	glUseProgram(main_program);

	glUniform1i(main_mat_diffuse_id, 0);
	glUniform1i(main_mat_specular_id, 1);	
	glUniform1i(main_mat_emission_id, 2);

	glUniform1f(main_light_constant_id, 1.0f);
	glUniform1f(main_light_linear_id, 0.09f);
	glUniform1f(main_light_quadratic_id, 0.032f);

	glUniform1i(main_light_tex_id, 3);

	glUseProgram(0);

	//	
	main_light_tex[0] = 0;
	puts("gen0");
	glGenTextures(1, main_light_tex);
	puts("gen1");
	glBindTexture(GL_TEXTURE_2D, main_light_tex[0]);

	puts("init");
	Game::Object::init_texture(&main_light_tex[0]);
	if (!main_light_tex[0]) {
		fprintf(stderr, "Failed to init_texture.\n");
		goto delete_vbos;
	}

	puts("set");
	res = Game::Object::set_texture(TEXTURE_PATHS[9]);
	if (res < 0) {
		fprintf(stderr, "Failed to set_texture.\n");
		goto delete_texture;
	}

	glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	puts("done");
	//


	light_program_tex_id = glGetUniformLocation(light_program, "tex");
	light_color_id = glGetUniformLocation(light_program, "lightColor");

	glUseProgram(light_program);

	glUniform1f(light_program_tex_id, 0);

	glUseProgram(0);

	// Matricies
	//

	main_model_id      = glGetUniformLocation(main_program, "model");
	main_view_id       = glGetUniformLocation(main_program, "view");
	main_projection_id = glGetUniformLocation(main_program, "projection");

	light_model_id      = glGetUniformLocation(light_program, "model");
	light_view_id       = glGetUniformLocation(light_program, "view");
	light_projection_id = glGetUniformLocation(light_program, "projection");

	key_states = SDL_GetKeyboardState(nullptr);

	//	Objects
	//
	objects[0] =  Object(main_model_id, vbos[0], TEXTURE_PATHS[0], TEXTURE_PATHS[1], nullptr,
		INDICIES, 18, true, &positions[0], &rotations[0], 0.0f, &scales[0], 16.0f);
	objects[1] =  Object(main_model_id, vbos[0], TEXTURE_PATHS[2], TEXTURE_PATHS[3], nullptr,
		&INDICIES[18], 6, true, &positions[1], &rotations[1], 0.0f, &scales[1], 16.0f);
	objects[2] =  Object(main_model_id, vbos[0], TEXTURE_PATHS[4], TEXTURE_PATHS[5], TEXTURE_PATHS[6],
		&INDICIES[24], 36, true, &positions[2], &rotations[2], 45.0f, &scales[2], 16.0f);
	objects[3] =  Object(light_model_id, vbos[0], TEXTURE_PATHS[7], TEXTURE_PATHS[8], nullptr,
		&INDICIES[24], 36, true, &positions[3], &rotations[3], 0.0f, &scales[3], 16.0f);

	res = objects[0].init();
	if (res < 0) {
		fprintf(stderr, "Failed to init objects[0].\n");
		goto delete_texture;
	}

	res = objects[1].init();
	if (res < 0) {
		fprintf(stderr, "Failed to init objects[1].\n");
		goto delete_texture;
	}

	res = objects[2].init();
	if (res < 0) {
		fprintf(stderr, "Failed to init objects[2].\n");
		goto delete_texture;
	}

	res = objects[3].init();
	if (res < 0) {
		fprintf(stderr, "Failed to init objects[3].\n");
		goto delete_texture;
	}

	// CLEANUP
	// -------

	return 0;

	delete_texture:
	glDeleteTextures(1, main_light_tex);

	delete_vbos:
	glDeleteBuffers(1, vbos);

	delete_light_program:
	glDeleteProgram(light_program);

	delete_program:
	glDeleteProgram(main_program);

	destroy_gl_ctx:
	SDL_GL_DestroyContext(gl_ctx);

	destroy_win:
	SDL_DestroyWindow(window);

	quit:
	SDL_Quit();

	return -1;
}

/*
================
Game::run_render_loop()
	stats Game render loop, 
	while Game is running
================
*/

int Game::run_render_loop()
{
	while (running) {
		glm::mat4 view;
	        glm::mat4 projection = glm::mat4(1.0f);
		std::chrono::time_point cur_tp =
			std::chrono::steady_clock::now();
		deltatime = (float)
			std::chrono::
			duration_cast<std::chrono::milliseconds>
			(cur_tp - prev_tp).count()
			* deltatime_coef;

		prev_tp = cur_tp;

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_EVENT_QUIT:
						running = false;
						break;
				case SDL_EVENT_WINDOW_RESIZED:
					SDL_GetWindowSizeInPixels(
						window, &win_w, &win_h);
					win_w_centered = win_w / 2.0f;
					win_h_centered = win_h / 2.0f;
					glViewport(0, 0, win_w, win_h);
				case SDL_EVENT_MOUSE_MOTION:
					process_mouse_motion();
					break;
			}
		}

		process_keyboard();

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);//try white
		glClear(GL_COLOR_BUFFER_BIT
			| GL_DEPTH_BUFFER_BIT);

		glUseProgram(main_program);

		// View and Projection matricies
		//

		view = glm::lookAt(cam_pos,
			cam_pos + cam_front, cam_up);
		projection = glm::perspective(
			glm::radians(45.0f),
			(float)win_w / (float)win_h,
			0.1f, 100.0f
		);

		glUniformMatrix4fv(main_view_id, 1, GL_FALSE,
			glm::value_ptr(view));
		glUniformMatrix4fv(main_projection_id, 1,
			GL_FALSE, glm::value_ptr(projection));

		// Light
		//

		glUniform3fv(main_view_pos_id, 1, glm::value_ptr(cam_pos));
		glUniform3fv(main_light_position_id, 1, glm::value_ptr(cam_pos));
		glUniform3fv(main_light_direction_id, 1, glm::value_ptr(cam_front));	
		glUniform1f(main_light_cut_off_id, glm::cos(glm::radians(12.5f)));
		glUniform1f(main_light_out_cut_off_id, glm::cos(glm::radians(17.5f)));

		glActiveTexture(GL_TEXTURE3);
		glBindTexture(GL_TEXTURE_2D, main_light_tex[0]);

		// Moodel0: Pyramid
		//

		glUniform3fv(main_light_ambient_id, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
		glUniform3fv(main_light_diffuse_id, 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(main_light_specular_id, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));	
		glUniform3fv(main_light_emission_id, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
		glUniform1f(main_mat_shininess_id, 32.0f);
	
		if (objects[0].get_position_ptr()->x >= 3.0f || objects[0].get_position_ptr()->x < -3.0f) {
			pyramid_move_coef *= -1;
		}
		
		objects[0].translate_add(glm::vec3(pyramid_move_coef, 0.0f, 0.0f));
		objects[0].rotate_add(glm::radians(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));

		objects[0].translate_perform();
		objects[0].rotate_perform();
		objects[0].scale_perform();

		objects[0].draw();

		// Model1: Plane
		//

		glUniform3fv(main_light_ambient_id, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
		glUniform3fv(main_light_diffuse_id, 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(main_light_specular_id, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));	
		glUniform3fv(main_light_emission_id, 1, glm::value_ptr(glm::vec3(0.0f, 0.0f, 0.0f)));
		glUniform1f(main_mat_shininess_id, 32.0f);

		objects[1].translate_perform();
		objects[1].rotate_perform();
		objects[1].scale_perform();

		objects[1].draw();

		// Model2: Cube(), LuckyBlock
		//		
		
		glUniform3fv(main_light_ambient_id, 1, glm::value_ptr(glm::vec3(0.1f, 0.1f, 0.1f)));
		glUniform3fv(main_light_diffuse_id, 1, glm::value_ptr(glm::vec3(0.8f, 0.8f, 0.8f)));
		glUniform3fv(main_light_specular_id, 1, glm::value_ptr(glm::vec3(1.0f, 1.0f, 1.0f)));
		glUniform3fv(main_light_emission_id, 1, glm::value_ptr(glm::vec3(0.5f, 0.5f, 0.5f)));
		glUniform1f(main_mat_shininess_id, 32.0f);

		//objects[2].rotate_add(glm::radians(0.75f), glm::vec3(1.0f));

		objects[2].translate_perform();
		objects[2].rotate_perform();
		objects[2].scale_perform();

		objects[2].draw();

		// Model3: Cube (light00)
		//

		glUseProgram(light_program);

		glUniformMatrix4fv(light_view_id, 1, GL_FALSE,
			glm::value_ptr(view));
		glUniformMatrix4fv(light_projection_id, 1,
			GL_FALSE, glm::value_ptr(projection));
		glUniform3fv(light_color_id, 1, light_color);

		objects[3].translate_perform();
		objects[3].rotate_perform();
		objects[3].scale_perform();

		objects[3].draw();

		// Stuff, Reseting data
		//

		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
		glUseProgram(0);

		SDL_GL_SwapWindow(window);
	}

	return 0;
}

/*
================
Game::create_program()
	creates single shader program
================
*/

unsigned int Game::create_program(const char *const vs_path,
                            	  const char *const fs_path) const
{
	if (!vs_path || ! fs_path) {
		fprintf(stderr, "Failed create_program. "
			"Argument is NULL.\n");
		return 0;
	}

	char 		        *shader_src     = nullptr;
	unsigned int             vertex_shr     = 0;
	unsigned int             fragment_shr   = 0;
	unsigned int             shader_program = 0;
	std::ifstream            shader_ifs;
	std::ifstream::pos_type  shader_len     = 0;
	char 			 info_log[256];
	int 			 res            = 0;

	// Vertex shader source
	//

	shader_ifs.open(vs_path, std::ios::in);
	if (!shader_ifs.is_open()) {
		fprintf(stderr, "Failed to open shader_ifs "
			"(VS_PATH).\n");
		goto err;
	}

	shader_ifs.seekg(0, shader_ifs.end);
	shader_len = shader_ifs.tellg();
	shader_ifs.seekg(0, shader_ifs.beg);

	shader_src = (char*)malloc(sizeof(char) * shader_len);
	if (!shader_src) {
		fprintf(stderr, "Failed to malloc shader_src.\n");
		goto err;
	}

	shader_ifs.read(shader_src, shader_len);
	shader_ifs.close();

	shader_src[shader_len] = '\0';
	
	// vertex shader
	//

	vertex_shr = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shr, 1, &shader_src, nullptr);
	std::free(shader_src);
	glCompileShader(vertex_shr);

	glGetShaderiv(vertex_shr, GL_COMPILE_STATUS, &res);
	if (!res) {
		glGetShaderInfoLog(vertex_shr, sizeof(info_log),
				nullptr, info_log);
		fprintf(stderr, "Failed to glCompileShader "
				"(vertex shader). Err: %s.\n",
				info_log);
		goto err;
	}

	// fragment shader source
	//

	shader_ifs.open(fs_path, std::ios::in);
	if (!shader_ifs.is_open()) {
		fprintf(stderr, "Failed to open shader_ifs "
			"(FS_PATH).\n");
		goto err;
	}

	shader_ifs.seekg(0, shader_ifs.end);
	shader_len = shader_ifs.tellg();
	shader_ifs.seekg(0, shader_ifs.beg);

	shader_src = (char*)malloc(sizeof(char) * shader_len);
	if (!shader_src) {
		fprintf(stderr, "Failed to malloc shader_src.\n");
		goto err;
	}

	shader_ifs.read(shader_src, shader_len);
	shader_ifs.close();

	shader_src[shader_len] = '\0';
	
	// fragment shader
	//

	fragment_shr = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shr, 1, &shader_src, nullptr);
	std::free(shader_src);
	glCompileShader(fragment_shr);

	glGetShaderiv(fragment_shr, GL_COMPILE_STATUS, &res);
	if (!res) {
		glGetShaderInfoLog(fragment_shr, sizeof(info_log),
			nullptr, info_log);
		fprintf(stderr, "Failed to glCompileShader "
			"(fragment shader). Err: %s.\n",
			info_log);
		glDeleteShader(vertex_shr);
		goto err;
	}

	// shader program
	//

	shader_program = glCreateProgram();
	glAttachShader(shader_program, vertex_shr);
	glAttachShader(shader_program, fragment_shr);
	glLinkProgram(shader_program);

	glGetProgramiv(shader_program, GL_LINK_STATUS, &res);
	if (!res) {
		glGetProgramInfoLog(shader_program,
			sizeof(info_log), nullptr, info_log);
		fprintf(stderr, "Failed to glLinkProgram. "
			"Err: %s.\n", info_log);
		glDeleteShader(vertex_shr);
		glDeleteShader(fragment_shr);
		goto err;
	}

	glDeleteShader(vertex_shr);
	glDeleteShader(fragment_shr);

	return shader_program;

	err:
	return 0;
}

/*
================
Game::process_keyboard()
	handles keyboard events (down, release and etc)
================
*/

void Game::process_keyboard()
{
	if (key_states[SDL_SCANCODE_ESCAPE]) {
		if (esc_released) {
			if (relative_moded) {
				SDL_SetWindowRelativeMouseMode(window, false);
				relative_moded = false;
			}
			else {
				SDL_SetWindowRelativeMouseMode(window, true);	
				relative_moded = true;		
			}
			esc_released = false;
		}
	}
	else if (!esc_released) {
		esc_released = true;
	}

	if (key_states[SDL_SCANCODE_W]) {
		cam_pos += glm::normalize(glm::vec3(cam_front.x, 0.0f, cam_front.z))
			* cam_trans_speed * deltatime;
	}
	if (key_states[SDL_SCANCODE_S]) {
		cam_pos -= glm::normalize(glm::vec3(cam_front.x, 0.0f, cam_front.z))
		 * cam_trans_speed * deltatime;
	}
	if (key_states[SDL_SCANCODE_A]) {
		cam_pos -= cam_right * cam_trans_speed * deltatime;
	}
	if (key_states[SDL_SCANCODE_D]) {
		cam_pos += cam_right * cam_trans_speed * deltatime;
	}

	if (key_states[SDL_SCANCODE_SPACE]) {
		cam_pos += world_up * cam_trans_speed * deltatime;
	}
	if (key_states[SDL_SCANCODE_LSHIFT]) {
		cam_pos -= world_up * cam_trans_speed * deltatime;
	}

	//	Model2: LuckyBlock
	//
	if (key_states[SDL_SCANCODE_LEFT]) {
		objects[2].translate_add(glm::vec3(-1.0f, 0.0f, 0.0f) * 0.25f * deltatime);
	}
	if (key_states[SDL_SCANCODE_RIGHT]) {
		objects[2].translate_add(glm::vec3(1.0f, 0.0f, 0.0f) * 0.25f * deltatime);
	}
	if (key_states[SDL_SCANCODE_UP]) {
		objects[2].translate_add(glm::vec3(0.0f, 0.0f, -1.0f) * 0.25f * deltatime);
	}
	if (key_states[SDL_SCANCODE_DOWN]) {
		objects[2].translate_add(glm::vec3(0.0f, 0.0f, 1.0f) * 0.25f * deltatime);
	}
}

/*
================
Game::process_mouse_motion()
	handles mouse motion
================
*/

void Game::process_mouse_motion(void)
{
	float x = 0.0f;
	float y = 0.0f;

	SDL_GetMouseState(&x, &y);

	static float last_x = x;
	static float last_y = y;
	static float yaw   = -90.0f;
	static float pitch = 1.0f;

	float offset_x;
	float offset_y;

	if (relative_moded) {
		offset_x = x - win_w_centered;
		offset_y = win_h_centered - y;
		SDL_WarpMouseInWindow(window, win_w_centered, win_h_centered);
	}
	else {
		offset_x = x - last_x;
		offset_y = last_y - y;
	}

	last_x = x;
	last_y = y;

	yaw   += offset_x * cam_rtn_speed;
	pitch += offset_y * cam_rtn_speed;

	if (pitch >= 89.0f) {
		pitch = 89.0f;
	}
	else if (pitch <= -89.0f) {
		pitch = -89.0f;
	}

	cam_front.x = std::cos(glm::radians(yaw)) *
		std::cos(glm::radians(pitch));
	cam_front.y = std::sin(glm::radians(pitch));
	cam_front.z = std::sin(glm::radians(yaw)) *
		std::cos(glm::radians(pitch));

	cam_front = glm::normalize(cam_front);

	cam_right = glm::normalize(glm::cross(cam_front, world_up));
	cam_up    = glm::normalize(glm::cross(cam_right, cam_front));
}
