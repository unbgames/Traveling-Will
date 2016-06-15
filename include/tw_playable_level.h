#ifndef TW_PLAYABLE_LEVEL_H
#define TW_PLAYABLE_LEVEL_H

#include "tw_will.h"
#include "tw_level.h"
#include "tw_button.h"
#include "tw_platform.h"

using std::string;
using std::shared_ptr;

using namespace ijengine;

class TWPlayableLevel : public TWLevel{
    public:
        TWPlayableLevel(const string& current_level, const string& next_level = "", const string audio_path = "", 
		int audio_duration = -1);
        ~TWPlayableLevel();

		bool done() const;
		string next() const;
		string audio() const;

		bool on_event(const GameEvent& event);

	protected:
		void update_self(unsigned now, unsigned last);
		void draw_self(Canvas *canvas, unsigned now, unsigned last);

	private:
        static const int GAME_EVENT_JUMP =              1 << 4;
        static const int GAME_EVENT_SLIDE_PRESSED =     1 << 5;
        static const int GAME_EVENT_SLIDE_RELEASED =    1 << 6;
        static const int GAME_EVENT_MENU_SELECT =       1 << 7;
        static const int GAME_EVENT_PUNCH =             1 << 11;
        static const int NUMBER_OF_SECTIONS =           7;
        static const int WILL_HEIGHT =                  45;
        static const int WILL_WIDTH =                   45;
        static const int COLLECTABLE_DIMENSION =        30;
        static const int COLLECTABLE_SIZE =             WILL_HEIGHT + COLLECTABLE_DIMENSION;
        static const int ENEMY_DIMENSION =              45;
        static const int ENEMY_SIZE =                   WILL_HEIGHT + ENEMY_DIMENSION;
        static const int INVALID =                      -10000000;
        static const int COLLECTABLE =                  0;
        static const int ENEMY =                        1; 
        static const int PLATFORM_SIZE =                142;

        bool m_is_punching, level_started, level_finished;
        
        int m_audio_duration, m_audio_counter;
        int n_screens, m_punch_counter;
        int n_collectables, n_enemies;
        int m_cur_collectable_it, m_cur_enemy_it;
        
        deque<int> enemy_type, collectable, enemy;
        deque<double> collectable_height, enemy_height, platform_height;
        deque<TWPlatform *> platforms;

        double m_x_speed, m_y_speed;
        double sprite_counter, m_sprite_speed;
        double m_camera_x, m_camera_y, m_reverse_camera_x, m_reverse_camera_y;
        double m_floor;

        TWWill * m_will;
        TWCollectable *m_cur_collectable;
        TWEnemy *m_cur_enemy;

        shared_ptr<Texture> m_progress_bar[3], m_will_progress_bar;
        shared_ptr<Texture> m_number, m_collectable_icon, m_floor_texture;

        void test_floor(unsigned now);
        void update_counters(unsigned now);
        void check_game_over();
        void update_platforms_position();
};

#endif
