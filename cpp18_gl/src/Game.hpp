#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <cstdio>
#include <chrono>
#include <fstream>
#include <cmath>

#include <SDL3/SDL.h>
//#include <SDL3/SDL_main.h>

#include <glad/glad.h>
#include <SDL3/SDL_opengl.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern "C" {
#include <libavformat/avformat.h>
#include <libavcodec/avcodec.h>
#include <libavutil/avutil.h>
}

class Game
{
public:
	Game(int win_width, int win_height);
	~Game(void);

	int 	     init(void);
	int 		 run_render_loop(void);

	unsigned int create_program(const char *const vs_path,
			    			    const char *const fs_path) const;
	void 		 process_keyboard(void);
	void 		 process_mouse_motion(void);
	
private:
	class Object {
	public:
		Object(unsigned int 	   model_mat_id,
			   unsigned int        vbo,
	 		   const char *const   tex0_path,
			   const char *const   tex1_path,
			   const char *const   tex2_path,
			   const unsigned int *indicies,
			   int                 verticies_len,
			   bool                has_normals,
			   glm::vec3          *pos,
			   glm::vec3		  *rotation,
			   float			   rotation_angle,
			   glm::vec3		  *scale,
			   const float         shin);
		Object(void);
		~Object(void);
		Object& operator=(const Game::Object& obj);
		
		bool is_valid(void) const;
		int  init(void);
		void draw(void);

		void translate_add(glm::vec3 *position = nullptr);
		void translate_add(glm::vec3 &&position);
		void translate_perform(void);
		void rotate_add(float angle = 0.0f, glm::vec3 *rotation = nullptr);
		void rotate_add(float angle, glm::vec3 &&rotation);
		void rotate_perform(void);
		void scale_add(glm::vec3 *scale = nullptr);
		void scale_add(glm::vec3 &&scale);
		void scale_perform(void);
		
		static void init_texture(unsigned int *texture);
		static int  set_texture(const char *const path);		

		unsigned int  get_model_mat_id(void) const;
		unsigned int  get_vao(void) const;
		unsigned int  get_vbo(void) const;
		unsigned int  get_ebo(void) const;
		unsigned int  get_verticies_len(void) const;	
		glm::mat4     get_model_mat(void) const;		
		glm::vec3     get_position(void) const;	
		float         get_rotation_angle(void) const;	
		glm::vec3     get_rotation(void) const;	
		glm::vec3     get_scale(void) const;	
		const float   get_shininess(void) const;
		const bool    get_has_normals(void) const;			
		void          cpy_texture_paths(char* (new_texture_paths)[3]) const;
		void          cpy_indicies(unsigned int **new_indicies) const;
	
		const glm::mat4 *const get_model_mat_ptr(void) const;		
		const glm::vec3 *const get_position_ptr(void) const;	
		const glm::vec3 *const get_rotation_ptr(void) const;	
		const glm::vec3 *const get_scale_ptr(void) const;	

	private:
		char         *TEXTURE_PATHS[3];
		unsigned int  model_mat_id;
		unsigned int  vao;
		unsigned int  vbo;
		unsigned int  ebo;
		unsigned int *indicies;
		unsigned int  verticies_len;
		unsigned int  textures[3]; //diffuse, specular
		glm::mat4 	  model_mat;
		glm::vec3     position;
		glm::vec3	  rotation;
		float    	  rotation_angle;
		glm::vec3	  scale;
		float         shininess;
		bool 	 	  has_normals;
		mutable bool  shares_data;	
	};


	static constexpr float VERTS[] = {
		/*	PYRAMID */
        //front
        -1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.447214f, 0.894427f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.447214f, 0.894427f,
         0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.0f, 0.447214f, 0.894427f,
        //back
         1.0f, -1.0f, -1.0f,  0.0f, 0.0f,  0.0f, 0.447214f, -0.894427f,
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.447214f, -0.894427f,
	 	 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.0f, 0.447214f, -0.894427f,
        //left
        -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -0.894427f, 0.447214f, 0.0f,
		-1.0f, -1.0f,  1.0f,  1.0f, 0.0f, -0.894427f, 0.447214f, 0.0f,
	 	 0.0f,  1.0f,  0.0f,  0.5f, 1.0f, -0.894427f, 0.447214f, 0.0f,
        //right
         1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.894427f, 0.447214f, 0.0f,
 	 	 1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.894427f, 0.447214f, 0.0f,
	 	 0.0f,  1.0f,  0.0f,  0.5f, 1.0f,  0.894427f, 0.447214f, 0.0f,
        //bottom & CUBEs
        -1.0f, -1.0f, -1.0f,  1.0f, 1.0f,  0.0f, -1.0f, 0.0f,
         1.0f, -1.0f, -1.0f,  0.0f, 1.0f,  0.0f, -1.0f, 0.0f,
	 	 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, -1.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, -1.0f, 0.0f,

		/*  PLANE */
		-1.0f,  1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
 		 1.0f,  1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
	 	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 1.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 1.0f, 0.0f,

		/*	CUBE */
		//front
		-1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  0.0f, 0.0f, 1.0f,
         1.0f, -1.0f,  1.0f,  1.0f, 0.0f,  0.0f, 0.0f, 1.0f,
	 	 1.0f,  1.0f,  1.0f,  1.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		-1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
		//back
	 	 1.0f, -1.0f, -1.0f,   0.0f, 0.0f, 0.0f, 0.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  0.0f, 0.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  0.0f, 0.0f, -1.0f,
	 	 1.0f,  1.0f, -1.0f,  0.0f, 1.0f,  0.0f, 0.0f, -1.0f,
		//left
		-1.0f, -1.0f, -1.0f,  0.0f, 0.0f, -1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f,  1.0f,  1.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		-1.0f,  1.0f, -1.0f,  0.0f, 1.0f, -1.0f, 0.0f, 0.0f,
		//right
	 	 1.0f,  1.0f, -1.0f,  1.0f, 1.0f,  1.0f, 0.0f, 0.0f,
 	 	 1.0f,  1.0f,  1.0f,  0.0f, 1.0f,  1.0f, 0.0f, 0.0f,
		 1.0f, -1.0f,  1.0f,  0.0f, 0.0f,  1.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f,  1.0f, 0.0f,  1.0f, 0.0f, 0.0f
		 //top = PLANEs top
	};

	static constexpr unsigned int INDICIES[] = {
		//front  PYRAMID
		0, 1, 2,
		//back   PYRAMID
		3, 4, 5,
		//left   PYRAMID
		6, 7, 8,
		//right  PYRAMID
		9, 10, 11,
		//bottom PYRAMID full PLANE
		12, 13, 14,
		14, 15, 12,

		//top    PLANE
		16, 17, 18,
		18, 19, 16,

		//front  CUBE
		20, 21, 22,
		22, 23, 20,
		//back   CUBE
		24, 25, 26,
		26, 27, 24,
		//left   CUBE
		28, 29, 30,
		30, 31, 28,
		//right  CUBE
		32, 33, 34,
		34, 35, 32,
		//bottom CUBE
		12, 13, 14,
		14, 15, 12,
		//top    CUBE
		16, 17, 18,
		18, 19, 16
	};
	static constexpr char *MAIN_VS_PATH = (char*)"../src/main_shader.vs";
	static constexpr char *MAIN_FS_PATH = (char*)"../src/main_shader.fs";
	static constexpr char *LIGHT_VS_PATH = (char*)"../src/light_shader.vs";
	static constexpr char *LIGHT_FS_PATH = (char*)"../src/light_shader.fs";
	static constexpr char *TEXTURE_PATHS[] = {
		(char*)"../resources/textures/texture00.png",
		(char*)"../resources/textures/texture00_specular.png",
		(char*)"../resources/textures/texture01.png",
		(char*)"../resources/textures/texture01_specular.png",
		(char*)"../resources/textures/texture03.png",
		(char*)"../resources/textures/texture03_specular.png",
		(char*)"../resources/textures/texture03_emission.png",
		(char*)"../resources/textures/texture02.png",
		(char*)"../resources/textures/texture02_specular.png",
		(char*)"../resources/textures/texture04_solid_color.png"
	};
	static constexpr float deltatime_coef = 0.1f;

	SDL_Window    *window;
	SDL_Event      event;
	SDL_GLContext  gl_ctx;
	bool           running;	
	int            res;

	int win_w;
	int win_h;
	float win_w_centered;
	float win_h_centered;

	unsigned int main_program;
	unsigned int light_program;

	unsigned int vaos[3];
	unsigned int vbos[1];
	unsigned int ebos[3];

	//unsigned int textures[5];
	unsigned int main_program_tex_id;
	unsigned int light_program_tex_id;

	unsigned int main_model_id;
	unsigned int main_view_id;
	unsigned int main_projection_id;

	unsigned int main_view_pos_id;

	unsigned int main_mat_diffuse_id;
	unsigned int main_mat_specular_id;
	unsigned int main_mat_emission_id;
	unsigned int main_mat_shininess_id;

	unsigned int main_light_ambient_id;
	unsigned int main_light_diffuse_id;
	unsigned int main_light_specular_id;
	unsigned int main_light_emission_id;

	unsigned int main_light_position_id;
	unsigned int main_light_direction_id;
	unsigned int main_light_cut_off_id;
	unsigned int main_light_out_cut_off_id;

	unsigned int main_light_constant_id;
	unsigned int main_light_linear_id;
	unsigned int main_light_quadratic_id;
	
	unsigned int main_light_tex_id;
	unsigned int main_light_tex[1];

	unsigned int light_model_id;
	unsigned int light_view_id;
	unsigned int light_projection_id;
	unsigned int light_color_id;
	
	float light_color[3];

	glm::vec3 world_up;
	glm::vec3 cam_pos;
	glm::vec3 cam_front;
	glm::vec3 cam_right;
	glm::vec3 cam_up;
	

	glm::vec3 positions[5];
	glm::vec3 rotations[4];
	glm::vec3 scales[4];

	float deltatime;
	
	float pyramid_move_coef;

	float rotation;
	std::chrono::time_point<std::chrono::steady_clock> prev_tp;

	float cam_trans_speed;
	float cam_rtn_speed;

	const bool *key_states;
	bool relative_moded;
	bool esc_released; 

	Object objects[4];
};

#endif /* !__GAME_HPP__ */