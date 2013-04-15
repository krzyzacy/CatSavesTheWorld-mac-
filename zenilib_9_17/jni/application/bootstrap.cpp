/* This file is part of the Zenipex Library (zenilib).
 * Copyleft (C) 2011 Mitchell Keith Bloch (bazald).
 *
 * This source file is simply under the public domain.
 */

#include <zenilib.h>

#if defined(_DEBUG) && defined(_WINDOWS)
#define DEBUG_NEW new(_NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

using namespace std;
using namespace Zeni;

const float framestep = 0.009f;

class Game_Object {
    
public:
    Game_Object(const Point2f &position_,
                const Vector2f &size_,
                const float &theta_ = 0.0f,
                const float &speed_ = 0.0f)
    : m_position(position_),
    m_size(size_),
    m_theta(theta_),
    m_speed(speed_)
    {
    }
    
    void move(const float &dist_x_, const float &dist_y_, string condition){
        
        if(condition == "black_normal" || condition == "black_jump" || condition == "mousemove"){
            if((m_position.x + dist_x_) < 275.0f){
                m_position.x = 275.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
            
            if(condition == "black_jump"){
                m_position.y += dist_y_; 
            }
            else{
                if((m_position.y + dist_y_) < 106.0f){
                    m_position.y = 106.0f;
                }
                else if((m_position.y + dist_y_) > 416.0f){
                    m_position.y = 416.0f;
                }
                else{
                    m_position.y += dist_y_; 
                }
            }
        }
        else if(condition == "fishbone_normal" || condition == "treemove"){
            m_position.x += dist_x_;
            m_position.y += dist_y_;
        }
        else if(condition == "HPBox_final"){
            if((m_position.x + dist_x_) < 135.0f){
                m_position.x = 135.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else if(condition == "HPBox_final_black"){
            if((m_position.x + dist_x_) < 630.0f){
                m_position.x = 630.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else if(condition == "HPBox_stage3"){
            if((m_position.x + dist_x_) < 25.0f){
                m_position.x = 25.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else if(condition == "HPBox_stage3_black"){
            if((m_position.x + dist_x_) < 500.0f){
                m_position.x = 500.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else if(condition == "HPBox_normal"){
            if((m_position.x + dist_x_) < 275.0f){
                m_position.x = 275.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else if(condition == "world_normal"){
            if((m_position.x + dist_x_) <= 100.0f){
                m_position.x = 0.0f;
            }
            else{
                m_position.x += dist_x_; 
            }
        }
        else{
            
        }
    }
    
    const Point2f & get_position() const {return m_position;}
    const Vector2f & get_size() const {return m_size;}
    
    const float get_radius() const {
        return 0.5f * m_size.magnitude();
    }
    
    // If you might delete base class pointers, you need a virtual destructor.
    virtual ~Game_Object() {}
    virtual void render() const = 0;
    
protected:
    void render(const String &texture, const Color &filter = Color()) const {
        // Use a helper defined in Zeni/EZ2D.h
        render_image(
                     texture, // which texture to use
                     m_position, // upper-left corner
                     m_position + m_size, // lower-right corner
                     m_theta, // rotation in radians
                     1.0f, // scaling factor
                     m_position + 0.5f * m_size, // point to rotate & scale about
                     false, // whether or not to horizontally flip the texture
                     filter); // what Color to "paint" the texture
    }
    
private:
    Point2f m_position; // Upper left corner
    Vector2f m_size; // (width, height)
    float m_theta;
    
    float m_speed;
};

class World : public Game_Object {
    
    public:
        World(const Point2f &position_,
                 const Vector2f &size_,
                 const float &theta_
                 )
        : Game_Object(position_, size_, theta_)
        {

        }
        
        int type;
    
        void render() const {
            if(type == 1){
                Game_Object::render("background_stage1");
            }
            else if(type == 0){
                Game_Object::render("background_tutorial");
            }
            else if(type == 2){
                Game_Object::render("background_stage2");
            }
            else if(type == 3){
                Game_Object::render("background_stage3");
            }
        }
    
};

class Gameover : public Game_Object {
    
public:
    Gameover(const Point2f &position_,
          const Vector2f &size_,
          const float &theta_
          )
    : Game_Object(position_, size_, theta_)
    {
        visible = 0;
        reset = false;
    }
    
    int visible;
    bool reset;
    
    void render() const {
        if(visible == 1){
            Game_Object::render("gameover");
        }
        else if(visible == 2){
            Game_Object::render("stageclear");
        }
        else if(visible == 3){
            Game_Object::render("finishscreen");
        }
    }
    
};

class Fishbone : public Game_Object{
    
    public:
        Fishbone(const Point2f &position_,
             const Vector2f &size_,
             const float &theta_
             )
        : Game_Object(position_, size_, theta_)
        {
            livetime = 0.0f;
            direction = true;
        }
    
        float livetime;
        bool direction;
    
        void render() const {
            if(direction){
                Game_Object::render("fishbone");
            }
            else{
                Game_Object::render("fishbone_flip");
            }
        }

};

class Arrow : public Game_Object{
    
public:
    Arrow(const Point2f &position_,
             const Vector2f &size_,
             const float &theta_
             )
    : Game_Object(position_, size_, theta_)
    {
        livetime = 0.0f;
        direction = true;
    }
    
    float livetime;
    bool direction;
    
    void render() const {
        if(direction){
            Game_Object::render("arrow");
        }
        else{
            Game_Object::render("arrow_flip");
        }
    }
    
};

class Thunder_arrow : public Game_Object{
    
public:
    Thunder_arrow(const Point2f &position_,
          const Vector2f &size_,
          const float &theta_
          )
    : Game_Object(position_, size_, theta_)
    {
        livetime = 0.0f;
        direction = true;
    }
    
    float livetime;
    bool direction;
    
    void render() const {
        Game_Object::render("thunder_arrow");
    }
    
};

class HPBox : public Game_Object{
    public:
        HPBox   (const Point2f &position_,
                 const Vector2f &size_,
                 const float &theta_
                 )
        : Game_Object(position_, size_, theta_)
        {
            dialog = 0;
        }
    
        int dialog;
                
        void render() const {
            
            if(dialog == 1){
                Game_Object::render("tutorial_dialog_1");
            }
            else if(dialog == 2){
                Game_Object::render("tutorial_dialog_2");
            }
            else if(dialog == 3){
                Game_Object::render("tutorial_dialog_3");
            }
            else if(dialog == 4){
                Game_Object::render("tutorial_dialog_4");
            }
            else if(dialog == 5){
                Game_Object::render("tutorial_dialog_5");
            }
            else if(dialog == 6){
                Game_Object::render("tutorial_dialog_6");
            }
            else if(dialog == 7){
                Game_Object::render("tutorial_dialog_7");
            }
            else if(dialog == 8){
                Game_Object::render("tutorial_dialog_8");
            }
            else if(dialog == 9){
                Game_Object::render("tutorial_dialog_9");
            }
            else if(dialog == 10){
                Game_Object::render("tutorial_dialog_10");
            }
            else if(dialog == 11){
                Game_Object::render("white_HP_2");
            }
            else if(dialog == 12){
                Game_Object::render("white_HP_3");
            }
            else if(dialog == 13){
                Game_Object::render("white_HP_4");
            }
            else if(dialog == 14){
                Game_Object::render("white_HP_5");
            }
            else if(dialog == 15){
                Game_Object::render("white_HP_6");
            }
            else if(dialog == 16){
                Game_Object::render("black_HP_1");
            }
            else if(dialog == 17){
                Game_Object::render("black_HP_2");
            }
            else if(dialog == 18){
                Game_Object::render("black_HP_3");
            }
            else if(dialog == 19){
                Game_Object::render("black_HP_4");
            }
            else if(dialog == 20){
                Game_Object::render("black_HP_5");
            }
            else if(dialog == 21){
                Game_Object::render("black_HP_6");
            }
            else if(dialog == 22){
                Game_Object::render("boss_archer_HP_1");
            }
            else if(dialog == 23){
                Game_Object::render("boss_archer_HP_2");
            }
            else if(dialog == 24){
                Game_Object::render("boss_archer_HP_3");
            }
            else if(dialog == 25){
                Game_Object::render("boss_archer_HP_4");
            }
            else if(dialog == 26){
                Game_Object::render("boss_archer_HP_5");
            }
            else if(dialog == 27){
                Game_Object::render("boss_archer_HP_6");
            }
            else if(dialog == 99){
                
            }
            else{
                Game_Object::render("white_HP_1");
            }
        }
};

class BlackCat : public Game_Object {
public:
    BlackCat(const Point2f &position_,
             const Vector2f &size_,
             const float &theta_
             )
    : Game_Object(position_, size_, theta_)
    {
        dual = false;
        status_counter = 0;
        livetime = 0;
        direction = true;
        current_pos = 0.0f;
        
        throw_fishbone = 0.0f;
        jump = 0.0f;
        defend = 0.0f;
        attack = 0.0f;
        
        HP = 100;
        
        hit = 0.0f;
        dead = false;
        
        thunder = 0.0f;
        
        timer = 0.0f;
    }
    
    bool dual;
    int status_counter;
    int livetime; 
    bool direction; // true -> forward .. false -> backward
    float current_pos;
    
    float throw_fishbone;
    
    float jump;
    
    int defend;
    
    float attack;
    
    int HP;
    
    float hit;
    
    bool dead;
    
    float thunder;
    
    float timer;
    
    Fishbone * skill_1() const {
        const Point2f position (get_position() );
        
        Fishbone *tmp;
        
        if(direction){
            tmp = new Fishbone(Point2f(position.x + 96.0f, position.y + 40.0f), Vector2f(96.0f, 96.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Fishbone(Point2f(position.x - 10.0f, position.y + 40.0f), Vector2f(96.0f, 96.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    void collide_with_arrow(list<Arrow *> &arrowlist ){
        if(HP > 0.0f){
            for(list<Arrow *>::iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    
                    if((get_position().x < (tmp.x + 25.0f)) &&
                       ((get_position().y + 20.0f < tmp.y) && 
                        (get_position().y + 128.0f > tmp.y))){
                           delete *it;
                           it = arrowlist.erase(it);
                           if(!defend || !direction){
                               HP -= 5;
                               hit = 0.01f;
                               attack = 0.0f;
                           }
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x + 40.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 25.0f > tmp.x) &&
                       ((get_position().y + 20.0f < tmp.y) && 
                        (get_position().y + 128.0f >= tmp.y))){
                       delete *it;
                       it = arrowlist.erase(it);
                       if(!defend || direction){
                           HP -= 5;
                           hit = 0.01f;
                           attack = 0.0f;
                       }
                   }
                }
            }
        }
    }
    
    void collide_with_thunder(list<Thunder_arrow *> &arrowlist ){
        if(HP > 0.0f){
            for(list<Thunder_arrow *>::iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    if((get_position().x < (tmp.x + 10.0f)) &&
                    ((get_position().y + 20.0f < tmp.y) && 
                     (get_position().y + 128.0f > tmp.y))){
                        delete *it;
                        it = arrowlist.erase(it);
                        if(!defend || !direction){
                            thunder = 100 * framestep;
                            attack = 0.0f;
                        }
                    }
                }
                else{
                    
                    if(get_position().x > (tmp.x + 40.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 40.0f > tmp.x) &&
                        ((get_position().y + 20.0f < tmp.y) && 
                        (get_position().y + 128.0f >= tmp.y))){
                        delete *it;
                        it = arrowlist.erase(it);
                        if(!defend || direction){
                            thunder = 100 * framestep;
                            attack = 0.0f;
                        }
                    }
                }
            }
        }
    }
    
    void render() const {
        
         if(dead){
             Game_Object::render("white_dead");
         }
         else if (thunder){
             Game_Object::render("white_thunder");
         }
         else if(hit){
             if(direction){
                 Game_Object::render("white_hit");
             }
             else{
                 Game_Object::render("white_hit_flip");
             }
         }
         else if(throw_fishbone){
             if(direction){
                 Game_Object::render("white_weapon_attack_1");
             }
             else{
                 Game_Object::render("white_weapon_attack_flip_1");
             }
         }
         else if(defend){
             if(direction){
                 Game_Object::render("white_defend_1");
             }
             else{
                 Game_Object::render("white_defend_flip_1");    
             }
         }
         else if(jump){
             if(jump > 40 * framestep){
                 if(direction){
                     Game_Object::render("white_jump_2");
                 }
                 else{
                     Game_Object::render("white_jump_flip_2");
                 }
             }
             else{
                 if(direction){
                     Game_Object::render("white_jump_1");
                 }
                 else{
                     Game_Object::render("white_jump_flip_1");
                 }
             }
         }
         else if(attack){
             if(direction){
                 if(attack > 20 * framestep){
                     Game_Object::render("white_weapon_ready");
                 }
                 else if(attack > 10 * framestep){
                     Game_Object::render("white_weapon_attack_2");
                 }
                 else{
                     Game_Object::render("white_weapon_attack_1");
                 }
             }
             else{
                 if(attack > 20 * framestep){
                     Game_Object::render("white_weapon_ready_flip");
                 }
                 else if(attack > 10 * framestep){
                     Game_Object::render("white_weapon_attack_flip_2");
                 }
                 else{
                     Game_Object::render("white_weapon_attack_flip_1");
                 }
             }
         }
         else{
             if(direction){
                 if(HP <= 40){
                     Game_Object::render("white_weak");
                 }
                 else{
                     if(status_counter == 0){
                         Game_Object::render("white_1");
                     }  
                     else{
                         Game_Object::render("white_2");
                     }
                 }
             }
             else{
                 if(HP <= 40){
                     Game_Object::render("white_weak_flip");
                 }
                 else{
                     if(status_counter == 0){
                         Game_Object::render("white_flip_1");
                     }
                     else{
                         Game_Object::render("white_flip_2");
                     }
                 }
            }
        }
    }
    
};

class Tree : public Game_Object {
    
public:
    Tree(const Point2f &position_,
         const Vector2f &size_,
         const float &theta_
         )
    : Game_Object(position_, size_, theta_)
    {
        HP = 100.0f;
    }
    
    float tree_pos[100];
    float HP;
    
    void collide_with_fishbone(list<Fishbone *> &fishbones ){
        if(HP >= 0.0f){
            for(list<Fishbone *>::iterator it = fishbones.begin(); it != fishbones.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                        
                    if((get_position().x < (tmp.x + 16.0f)) &&
                       ((get_position().y - 10.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP = 0;
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x - 11.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 112.0f > tmp.x) &&
                       ((get_position().y - 10.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP = 0;
                       }
                }
            }
        }
    }
    
    void under_attack(BlackCat blackie){
        if(abs(blackie.get_position().x - get_position().x) < 150.0f || HP >= 0 ){
            if(abs(blackie.get_position().y - get_position().y) < 150.0f){
                if(blackie.direction){
                    
                    if(get_position().x < blackie.get_position().x - 30.0f){
                        return;
                    }
                    
                    if((get_position().x < blackie.get_position().x + 60.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 30.0f))
                    {
                        HP = 0;
                    }
                }
                else{
                    
                    if(get_position().x > blackie.get_position().x + 5.0f){
                        return;
                    }
                    
                    if((get_position().x > blackie.get_position().x - 75.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 30.0f))
                    {
                        HP = 0;
                    }
                }
            }
        }
    }
    
    void render() const {
        if(HP >= -300.0f && HP <= 0){
            Game_Object::render("tree_damaged");
        }
        else if(HP > 0){
            Game_Object::render("tree");
        }
        else{
            
        }
    }
    
};

class Mouse : public Game_Object {
    
public:
    Mouse(const Point2f &position_,
         const Vector2f &size_,
         const float &theta_
         )
    : Game_Object(position_, size_, theta_)
    {
        direction = true;
        state = 0;
        HP = 30;
        
        hit = 0.0f;
        attack = 0.0f;
        alert = false;
    }
    
    bool direction;
    int state;
    int HP;
    
    float hit;
    float attack;
    bool alert;
    
    void mouse_move(BlackCat blackie, float timestep){
        if(HP <= 0){
            return;
        }
        
        if(attack > 0){
            attack += timestep;
            if(attack > 120 * framestep){
                attack = 0.0f;
            }
            return;
        }
        
        if(hit > 0){
            hit += timestep;
            if(hit > 50 * framestep){
                hit = 0.0f;
            }
            return;
        }
        
        Vector2f ret;
        ret.x = 0.0f;
        ret.y = 0.0f;
        
        bool xmove = false, ymove = false;
        
        float xdis = get_position().x - 30.0f - blackie.get_position().x;
        float ydis = get_position().y - 20.0f - blackie.get_position().y;
        //float theta = xdis / ydis;
        
        if(abs(xdis) < 350.0f){
            alert = true;
        }
        else{
            alert = false;
        }
        
        if(!alert){
            return;
        }
        
        if(xdis > 0.0f){
            direction = true;
        }
        else{
            direction = false;
        }
        
        if(abs(xdis) >= 60.0f){
            ret.x = - timestep * (50.0f - rand()%50) * abs(xdis) / xdis;
            xmove = true;
        }
        
        if(abs(ydis) >= 5.0f){
            ret.y = - timestep * (50.0f - rand()%50) * abs(ydis) / ydis;
            ymove = true;
        }
        
        move(ret.x, ret.y, "mousemove");
        
        if(!xmove && !ymove){
            if(rand()%10 == 1){
                // attack
                attack = framestep;
            }
            else if(rand()%5 == 2) {
                ret.x = timestep * (rand()%100 - rand()%100);
                ret.y = timestep * (rand()%100 - rand()%100);
                move(ret.x, ret.y, "mousemove");
            }
            else{
                
            }
        }
        
    }
    
    void collide_with_fishbone(list<Fishbone *> &fishbones ){
        if(HP >= 0.0f){
            for(list<Fishbone *>::iterator it = fishbones.begin(); it != fishbones.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    
                    if((get_position().x < (tmp.x + 16.0f)) &&
                       ((get_position().y - 20.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x - 11.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 75.0f > tmp.x) &&
                       ((get_position().y - 20.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
            }
        }
    }
    
    void under_attack(BlackCat blackie){
        if(abs(blackie.get_position().x - get_position().x) < 150.0f || HP >= 0 ){
            if(abs(blackie.get_position().y - get_position().y) < 150.0f){
                if(blackie.direction){
                    
                    if(get_position().x < blackie.get_position().x){
                        return;
                    }
                    
                    if((get_position().x < blackie.get_position().x + 100.0f) && 
                       (get_position().y < blackie.get_position().y + 40.0f) &&
                       (get_position().y > blackie.get_position().y - 20.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
                else{
                    
                    if(get_position().x > blackie.get_position().x + 30.0f){
                        return;
                    }
                    
                    if((get_position().x > blackie.get_position().x - 70.0f) && 
                       (get_position().y < blackie.get_position().y + 40.0f) &&
                       (get_position().y > blackie.get_position().y - 20.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
            }
        }
    }
    
    void render() const {
        
        if(HP <= 0){
            Game_Object::render("mouse_dead");
        }
        else if(hit){
            if(direction){
                Game_Object::render("mouse");
            }
            else{
                Game_Object::render("mouse_flip");
            }
        }
        else if(attack){
            if(direction){
                if(attack > 40 * framestep){
                    Game_Object::render("mouse_attack_2");
                }
                else{
                    Game_Object::render("mouse_attack_1");
                }
            }
            else{
                if(attack > 40 * framestep){
                    Game_Object::render("mouse_attack_flip_2");
                }
                else{
                    Game_Object::render("mouse_attack_flip_1");
                }
            }
        }
        else{
            if(direction){
                if(state == 0){
                    Game_Object::render("mouse_move_1");
                }
                else{
                    Game_Object::render("mouse_move_2");
                }
            }
            else{
                if(state == 0){
                    Game_Object::render("mouse_move_flip_1");
                }
                else{
                    Game_Object::render("mouse_move_flip_2");
                }
            }
        }
    }
    
};

class Archer : public Game_Object {
    
public:
    Archer(const Point2f &position_,
          const Vector2f &size_,
          const float &theta_
          )
    : Game_Object(position_, size_, theta_)
    {
        direction = true;
        state = 0;
        HP = 40;
        
        hit = 0.0f;
        attack = 0.0f;
        alert = false;
    }
    
    bool direction;
    int state;
    int HP;
    
    float hit;
    float attack;
    bool alert;
    
    Arrow * skill_1() const {
        const Point2f position (get_position() );
        
        Arrow *tmp;
        
        if(direction){
            tmp = new Arrow(Point2f(position.x - 40.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Arrow(Point2f(position.x + 100.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    void mouse_move(BlackCat blackie, float timestep){
        if(HP <= 0){
            return;
        }
        
        if(attack > 0){
            attack += timestep;
            if(attack > 125 * framestep){
                attack = 0.0f;
            }
            return;
        }
        
        if(hit > 0){
            hit += timestep;
            if(hit > 50 * framestep){
                hit = 0.0f;
            }
            return;
        }
        
        Vector2f ret;
        ret.x = 0.0f;
        ret.y = 0.0f;
        
        bool ymove = false;
        
        float xdis = get_position().x - 30.0f - blackie.get_position().x;
        float ydis = get_position().y - 20.0f - blackie.get_position().y;
        //float theta = xdis / ydis;
        
        if(abs(xdis) < 350.0f){
            alert = true;
        }
        else{
            alert = false;
        }
        
        if(!alert){
            return;
        }
        
        if(xdis > 0.0f){
            direction = true;
        }
        else{
            direction = false;
        }
        
        if(abs(xdis) >= 60.0f){
            ret.x = - timestep * (10.0f - rand()%10) * abs(xdis) / xdis;
        }
        
        if(abs(ydis) >= 50.0f){
            ret.y = - timestep * (50.0f - rand()%50) * abs(ydis) / ydis;
            ymove = true;
        }
        
        move(ret.x, ret.y, "mousemove");
        
        if(!ymove){
            if(rand()%75 == 1){
                // attack
                attack = framestep;
            }
            else if(rand()%10 == 2) {
                ret.x = timestep * (rand()%100 - rand()%100);
                ret.y = timestep * (rand()%100 - rand()%100);
                move(ret.x, ret.y, "mousemove");
            }
            else{
                
            }
        }
        
    }
    
    void collide_with_fishbone(list<Fishbone *> &fishbones ){
        if(HP >= 0.0f){
            for(list<Fishbone *>::iterator it = fishbones.begin(); it != fishbones.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    
                    if((get_position().x < (tmp.x + 16.0f)) &&
                       ((get_position().y - 30.0f < tmp.y) && 
                        (get_position().y + 50.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x - 11.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 75.0f > tmp.x) &&
                       ((get_position().y - 30.0f < tmp.y) && 
                        (get_position().y + 50.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
            }
        }
    }
    
    void under_attack(BlackCat blackie){
        if(abs(blackie.get_position().x - get_position().x) < 150.0f || HP >= 0 ){
            if(abs(blackie.get_position().y - get_position().y) < 150.0f){
                if(blackie.direction){
                    
                    if(get_position().x < blackie.get_position().x + 25.0f){
                        return;
                    }
                    
                    if((get_position().x < blackie.get_position().x + 100.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 10.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
                else{
                    
                    if(get_position().x > blackie.get_position().x + 25.0f){
                        return;
                    }
                    
                    if((get_position().x > blackie.get_position().x - 60.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 10.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
            }
        }
    }
    
    void render() const {
        
        if(HP <= 0){
            Game_Object::render("archer_dead");
        }
        else if(hit){
            if(direction){
                Game_Object::render("archer_hit");
            }
            else{
                Game_Object::render("archer_hit_flip");
            }
        }
        else if(attack){
            if(direction){
                if(attack > 50 * framestep){
                    Game_Object::render("archer_2");
                }
                else{
                    Game_Object::render("archer_attack");
                }
            }
            else{
                if(attack > 50 * framestep){
                    Game_Object::render("archer_flip_2");
                }
                else{
                    Game_Object::render("archer_attack_flip");
                }
            }
        }
        else{
            if(direction){
                if(state == 0){
                    Game_Object::render("archer_1");
                }
                else{
                    Game_Object::render("archer_2");
                }
            }
            else{
                if(state == 0){
                    Game_Object::render("archer_flip_1");
                }
                else{
                    Game_Object::render("archer_flip_2");
                }
            }
        }
    }
    
};

class Boss_Archer : public Game_Object {
    
public:
    Boss_Archer(const Point2f &position_,
           const Vector2f &size_,
           const float &theta_
           )
    : Game_Object(position_, size_, theta_)
    {
        direction = true;
        state = 0;
        HP = 100;
        
        hit = 0.0f;
        attack = 0.0f;
        alert = false;
    }
    
    bool direction;
    int state;
    int HP;
    
    float hit;
    float attack;
    bool alert;
    
    Arrow * skill_1() const {
        const Point2f position (get_position() );
        
        Arrow *tmp;
        
        if(direction){
            tmp = new Arrow(Point2f(position.x - 40.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Arrow(Point2f(position.x + 100.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Arrow * skill_2() const {
        const Point2f position (get_position() );
        
        Arrow *tmp;
        
        if(direction){
            tmp = new Arrow(Point2f(position.x - 40.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Arrow(Point2f(position.x + 100.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Arrow * skill_3() const {
        const Point2f position (get_position() );
        
        Arrow *tmp;
        
        if(direction){
            tmp = new Arrow(Point2f(position.x - 40.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Arrow(Point2f(position.x + 100.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder3() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder1() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder2() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    void mouse_move(BlackCat blackie, float timestep){
        if(HP <= 0){
            return;
        }
        
        if(attack > 0){
            attack += timestep;
            if(attack > 100 * framestep){
                attack = 0.0f;
            }
            return;
        }
        
        if(hit > 0){
            hit += timestep;
            if(hit > 20 * framestep){
                hit = 0.0f;
            }
            return;
        }
        
        Vector2f ret;
        ret.x = 0.0f;
        ret.y = 0.0f;
        
        bool ymove = false;
        
        float xdis = get_position().x - 30.0f - blackie.get_position().x;
        float ydis = get_position().y - 20.0f - blackie.get_position().y;
        //float theta = xdis / ydis;
        
        if(abs(xdis) < 475.0f){
            alert = true;
        }
        else{
            alert = false;
        }
        
        if(!alert){
            return;
        }
        
        if(xdis > 0.0f){
            direction = true;
        }
        else{
            direction = false;
        }
        
        if(abs(xdis) >= 60.0f){
            ret.x = - timestep * (10.0f - rand()%10) * abs(xdis) / xdis;
        }
        
        if(abs(ydis) >= 50.0f){
            ret.y = - timestep * (50.0f - rand()%50) * abs(ydis) / ydis;
            ymove = true;
        }
        
        move(ret.x, ret.y, "mousemove");
        
        if(!ymove){
            if(rand()%40 == 1){
                // attack
                attack = framestep;
            }
            else if(rand()%10 == 2) {
                ret.x = timestep * (rand()%100 - rand()%100);
                ret.y = timestep * (rand()%100 - rand()%100);
                move(ret.x, ret.y, "mousemove");
            }
            else{
                
            }
        }
        
    }
    
    void collide_with_fishbone(list<Fishbone *> &fishbones ){
        if(HP >= 0.0f){
            for(list<Fishbone *>::iterator it = fishbones.begin(); it != fishbones.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    
                    if((get_position().x < (tmp.x + 16.0f)) &&
                       ((get_position().y - 30.0f < tmp.y) && 
                        (get_position().y + 50.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x - 11.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 75.0f > tmp.x) &&
                       ((get_position().y - 30.0f < tmp.y) && 
                        (get_position().y + 50.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                       }
                }
            }
        }
    }
    
    void under_attack(BlackCat blackie){
        if(abs(blackie.get_position().x - get_position().x) < 150.0f || HP >= 0 ){
            if(abs(blackie.get_position().y - get_position().y) < 150.0f){
                if(blackie.direction){
                    
                    if(get_position().x < blackie.get_position().x + 25.0f){
                        return;
                    }
                    
                    if((get_position().x < blackie.get_position().x + 100.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 10.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
                else{
                    
                    if(get_position().x > blackie.get_position().x + 25.0f){
                        return;
                    }
                    
                    if((get_position().x > blackie.get_position().x - 60.0f) && 
                       (get_position().y < blackie.get_position().y + 50.0f) &&
                       (get_position().y > blackie.get_position().y - 10.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                    }
                }
            }
        }
    }
    
    void render() const {
        
        if(HP <= 0){
            Game_Object::render("boss_archer_dead");
        }
        else if(hit){
            if(direction){
                Game_Object::render("boss_archer_hit");
            }
            else{
                Game_Object::render("boss_archer_hit_flip");
            }
        }
        else if(attack){
            if(direction){
                if(attack > 50 * framestep){
                    Game_Object::render("boss_archer_2");
                }
                else{
                    Game_Object::render("boss_archer_attack");
                }
            }
            else{
                if(attack > 50 * framestep){
                    Game_Object::render("boss_archer_flip_2");
                }
                else{
                    Game_Object::render("boss_archer_attack_flip");
                }
            }
        }
        else{
            if(direction){
                if(state == 0){
                    Game_Object::render("boss_archer_1");
                }
                else{
                    Game_Object::render("boss_archer_2");
                }
            }
            else{
                if(state == 0){
                    Game_Object::render("boss_archer_flip_1");
                }
                else{
                    Game_Object::render("boss_archer_flip_2");
                }
            }
        }
    }
    
};

class CatBoss : public Game_Object {
    
public:
    CatBoss(const Point2f &position_,
          const Vector2f &size_,
          const float &theta_
          )
    : Game_Object(position_, size_, theta_)
    {
        dual = false;
        direction = false;
        state = 0;
        HP = 230;
        
        hit = 0.0f;
        attack = 0.0f;
        alert = false;
        defend = 0;
        
        ultra = 2;
        thunder = 0.0f;
        
        blinkcount = 0;
    }
    bool dual;
    
    bool direction;
    int state;
    int HP;
    
    float hit;
    float attack;
    bool alert;
    int defend;
    
    int ultra;
    float thunder;
    int blinkcount;
    
    Thunder_arrow * throw_thunder() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(!direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y + 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder1() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(!direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y + 100.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder2() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(!direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y + 150.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y + 150.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder3() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(!direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y - 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y - 50.0f), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    Thunder_arrow * throw_thunder4() const {
        const Point2f position (get_position() );
        
        Thunder_arrow *tmp;
        
        if(!direction){
            tmp = new Thunder_arrow(Point2f(position.x - 40.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        else{
            tmp = new Thunder_arrow(Point2f(position.x + 100.0f, position.y), Vector2f(96.0f, 12.0f), Global::pi * 0.0f);
        }
        
        tmp->direction = direction;
        
        return tmp;
    }
    
    void Boss_move(BlackCat blackie, float timestep){
        if(HP <= 0){
            return;
        }
        
        if(thunder > 0){
            return;
        }
        
        if(HP <= 110 && ultra > 1){
            ultra--;
            thunder = framestep;
            if(rand()%2 == 1){
                move(275.0f, 0.0f, "black_normal");
                direction = false;
            }
            else{
                move(-225.0f, 0.0f, "black_normal");
                direction = true;
            }
            return;
        }
        
        if(HP <= 50 && ultra > 0){
            ultra--;
            thunder = framestep;
            if(rand()%2 == 1){
                move(300.0f, 0.0f, "black_normal");
                direction = false;
            }
            else{
                move(-250.0f, 0.0f, "black_normal");
                direction = true;
            }
            return;
        }
        
        if(attack > 0){
            attack += timestep;
            if(attack > 100 * framestep){
                attack = 0.0f;
            }
            return;
        }
        
        if(hit > 0){
            hit += timestep;
            if(hit > 20 * framestep){
                hit = 0.0f;
            }
            return;
        }
        
        Vector2f ret;
        ret.x = 0.0f;
        ret.y = 0.0f;
        
        bool xmove = false, ymove = false;
        
        float xdis = get_position().x + 15.0f - blackie.get_position().x;
        float ydis = get_position().y + 20.0f - blackie.get_position().y;
        //float theta = xdis / ydis;
        
        if(abs(xdis) < 550.0f){
            alert = true;
        }
        else{
            alert = false;
        }
        
        if(!alert){
            return;
        }
        
        if(xdis > 0.0f){
            direction = false;
        }
        else{
            direction = true;
        }
        
        if(abs(xdis) >= 55.0f){
            ret.x = - timestep * (125.0f - rand()%125) * abs(xdis) / xdis;
            xmove = true;
        }
        
        if(abs(ydis) >= 25.0f){
            ret.y = - timestep * (50.0f) * abs(ydis) / ydis;
            ymove = true;
        }
        
        move(ret.x, ret.y, "mousemove");
        
        if(!xmove && !ymove){
            if(rand()%7 == 1){
                // attack
                attack = framestep;
            }
            else if(rand()%5 == 2) {
                ret.x = timestep * (rand()%100 - rand()%100);
                ret.y = timestep * (rand()%100 - rand()%100);
                move(ret.x, ret.y, "mousemove");
            }
            else{
                
            }
        }
        
    }
    
    void blink(){
        
        if(dual){
            return;
        }
        
        if(HP % 30 == 0 && HP > 0){
            
            blinkcount++;
            if(rand()%2 == 1){
                move(150.0f, 0.0f, "black_normal");
                direction = false;
            }
            else{
                move(-150.0f, 0.0f, "black_normal");
                direction = true;
            }
        }
    }
    
    void collide_with_fishbone(list<Fishbone *> &fishbones ){
        if(HP >= 0.0f){
            for(list<Fishbone *>::iterator it = fishbones.begin(); it != fishbones.end(); ++it){
                Point2f tmp = (*it)->get_position();
                if((*it)->direction){
                    
                    if(get_position().x < (tmp.x - 85.0f)){
                        continue;
                    }
                    
                    if((get_position().x < (tmp.x + 16.0f)) &&
                       ((get_position().y - 20.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                           
                           blink();
                       }
                }
                else{
                    
                    if(get_position().x > (tmp.x - 11.0f)){
                        continue;
                    }
                    
                    if((get_position().x + 75.0f > tmp.x) &&
                       ((get_position().y - 20.0f < tmp.y) && 
                        (get_position().y + 96.0f > tmp.y))){
                           delete *it;
                           it = fishbones.erase(it);
                           HP -= 10;
                           hit = framestep;
                           attack = 0.0f;
                           
                           blink();
                       }
                }
            }
        }
    }
    
    void under_attack(BlackCat blackie){
        if(abs(blackie.get_position().x - get_position().x) < 150.0f || HP >= 0 ){
            if(abs(blackie.get_position().y - get_position().y) < 150.0f){
                if(blackie.direction){
                    
                    if(get_position().x < blackie.get_position().x - 15.0f){
                        return;
                    }
                    
                    if((get_position().x < blackie.get_position().x + 45.0f) && 
                       (get_position().y < blackie.get_position().y + 10.0f) &&
                       (get_position().y > blackie.get_position().y - 50.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                        
                        blink();
                    }
                }
                else{
                    
                    if(get_position().x > blackie.get_position().x + 15.0f){
                        return;
                    }
                    
                    if((get_position().x > blackie.get_position().x - 75.0f) && 
                       (get_position().y < blackie.get_position().y + 10.0f) &&
                       (get_position().y > blackie.get_position().y - 50.0f))
                    {
                        HP -= 10;
                        hit = framestep;
                        attack = 0.0f;
                        
                        blink();
                    }
                }
            }
        }
    }
    
    void render() const {
        
        if(HP <= 0){
            Game_Object::render("black_dead");
        }
        else if(thunder && !dual){
            if(direction){
                if(thunder > 175 * framestep){
                    Game_Object::render("black_burn");
                }
                else if(thunder > 90 * framestep){
                    Game_Object::render("black_thunder_1");
                }
                else if(thunder > 40 * framestep){
                    Game_Object::render("black_thunder_2");
                }
            }
            else{
                if(thunder > 175 * framestep){
                    Game_Object::render("black_burn_flip");
                }
                else if(thunder > 90 * framestep){
                    Game_Object::render("black_thunder_flip_1");
                }
                else if(thunder > 40 * framestep){
                    Game_Object::render("black_thunder_flip_2");
                }
            }
        }
        else if(thunder && dual){
            if(direction){
                if(thunder > 15 * framestep){
                    Game_Object::render("black_thunder_1");
                }
                else{
                    Game_Object::render("black_thunder_2");
                }
            }
            else{
                if(thunder > 15 * framestep){
                    Game_Object::render("black_thunder_flip_1");
                }
                else{
                    Game_Object::render("black_thunder_flip_2");
                }
            }
        }
        else if(defend){
            if(direction){
                Game_Object::render("black_thunder_1");
            }
            else{
                Game_Object::render("black_thunder_flip_1");
            }
        }
        else if(hit){
            if(direction){
                Game_Object::render("black_hit");
            }
            else{
                Game_Object::render("black_hit_flip");
            }
        }
        else if(attack){
            if(direction){
                if(attack > 17 * framestep){
                    Game_Object::render("black_attack_2");
                }
                else if(attack < 45 * framestep){
                    Game_Object::render("black_attack_1");
                }
            }
            else{
                if(attack > 17 * framestep){
                    Game_Object::render("black_attack_flip_2");
                }
                else if(attack < 45 * framestep){
                    Game_Object::render("black_attack_flip_1");
                }
            }
        }
        else{
            if(direction){
                if (HP <= 40) {
                    Game_Object::render("black_weak");
                }
                else{
                    if(state == 0){
                        Game_Object::render("black_1");
                    }
                    else{
                        Game_Object::render("black_2");
                    }
                }
            }
            else{
                if(HP <= 40){
                    Game_Object::render("black_weak_flip");
                }
                else{
                    if(state == 0){
                        Game_Object::render("black_flip_1");
                    }
                    else{
                        Game_Object::render("black_flip_2");
                    }
                }
            }
        }
    }
};

class Dual_State : public Gamestate_Base {
    Dual_State(const Dual_State &);
    Dual_State operator=(const Dual_State &);
    
public:
    Dual_State()
    : 
    world(Point2f(0.0f, 0.0f), Vector2f(4096.0f, 1024.0f), Global::pi * 0.0f),
    blackie(Point2f(960.0f, 250.0f), Vector2f(164.0f, 164.0f), Global::pi * 0.0f),
    boss(Point2f(1320.0f, 250.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    avartar(Point2f(820.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    avartar1(Point2f(1315.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    actionlock(false),
    m_right(false),
    m_left(false),
    m_up(false),
    m_down(false),
    m_attack(false),
    m_jump(false),
    m_defense(false),
    boss_right(false),
    boss_left(false),
    boss_up(false),
    boss_down(false),
    boss_attack(false),
    boss_jump(false),
    boss_defense(false),
    boss_thunder(false),
    m_time_passed(0.0f),
    skill_1_throw_bone(false),
    w_score(0),
    b_score(0),
    m_restart(false),
    score_updated(false)
    {
        set_pausable(true);
        m_chrono.start();
        
        world.type = 3;
        boss.HP = 100;
        boss.dual = true;
        
        get_Sound().set_BGM("sfx/test");
        get_Sound().set_BGM_looping(1);
        get_Sound().play_BGM();
        
    }
    
private:
    void on_push() {
        get_Window().mouse_hide(true);
        //get_Window().mouse_grab(true);
    }
    
    void on_pop() {
        //get_Window().mouse_grab(false);
        get_Window().mouse_hide(false);
    }
    
    void on_key(const SDL_KeyboardEvent &event) {
        
        switch(event.keysym.sym) {
            case SDLK_w:
                m_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_a:
                m_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_s:
                m_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_d:
                m_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_b:
                m_defense = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_defense = false;
                }
                else{
                    actionlock = true;
                    m_left = false;
                    m_right = false;
                }
                break;
                
            case SDLK_v:
                m_jump = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_jump = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_g:
                m_attack = event.type == SDL_KEYDOWN;
                if((m_left || m_right) && m_down && !actionlock){
                    skill_1_throw_bone = true;
                    actionlock = true;
                    m_attack = false;
                }
                else if(actionlock){
                    m_attack = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_UP:
                boss_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_LEFT:
                boss_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_DOWN:
                boss_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_RIGHT:
                boss_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_k:
                boss_defense = event.type == SDL_KEYDOWN;
                if(boss_actionlock){
                    boss_defense = false;
                }
                else{
                    boss_actionlock = true;
                    boss_left = false;
                    boss_right = false;
                }
                break;
                
            case SDLK_j:
                boss_attack = event.type == SDL_KEYDOWN;
                if((boss_left || boss_right) && boss_down && !boss_actionlock){
                    boss_thunder = true;
                    boss_actionlock = true;
                    boss_attack = false;
                }
                else if(boss_actionlock){
                    boss_attack = false;
                }
                else{
                    boss_actionlock = true;
                }
                break;
                
            case SDLK_m:
                m_restart = event.type == SDL_KEYDOWN;
                break;
                
            default:
                Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
                break;
        }
    }
    
    void perform_logic(){
        const float time_passed = m_chrono.seconds();
        const float time_step = time_passed - m_time_passed;
        m_time_passed = time_passed;
        
        if(time_passed - blackie.livetime > 1.0f) {
            
            blackie.livetime = time_passed;
            
            if(blackie.status_counter == 0){
                blackie.status_counter = 1;
            }
            else{
                blackie.status_counter = 0;
            }
            
            if(boss.state == 0){
                boss.state = 1;
            }
            else{
                boss.state = 0;
            }
        }
        /* test code for being hit */
        
        
        if(blackie.hit > (15 + rand()%30) * framestep){
            actionlock = false;
            blackie.hit = 0;
        }
        
        if(boss.hit > (15 + rand()%30) * framestep){
            boss_actionlock = false;
            boss.hit = 0;
        }
        
        if(blackie.thunder > 250 * framestep){
            blackie.thunder = 0;
        }
        
        if(blackie.HP <= 0){
            blackie.dead = true;
            avartar.dialog = 15;
        }
        else{
            if(blackie.HP >= 90){
                avartar.dialog = 0;
            }
            else if(blackie.HP >= 70){
                avartar.dialog = 11;
            }
            else if(blackie.HP >= 50){
                avartar.dialog = 12;
            }
            else if(blackie.HP >= 30){
                avartar.dialog = 13;
            }
            else{
                avartar.dialog = 14;
            }
        }
        
        if(boss.HP <= 0){
            avartar1.dialog = 21;
        }
        else{
            if(boss.HP >= 90){
                avartar1.dialog = 16;
            }
            else if(boss.HP >= 70){
                avartar1.dialog = 17;
            }
            else if(boss.HP >= 50){
                avartar1.dialog = 18;
            }
            else if(boss.HP >= 30){
                avartar1.dialog = 19;
            }
            else{
                avartar1.dialog = 20;
            }
        }
        
        if(blackie.HP <= 0 || boss.HP <= 0){
            
            if(!score_updated){
                if(blackie.HP <= 0){
                    b_score ++;
                    score_updated = true;
                }
                else{
                    w_score ++;
                    score_updated = true;
                }
            }
            
            if(dead_timer.is_running()){
                if(m_restart){
                    get_Sound().set_BGM("sfx/test");
                    get_Sound().set_BGM_looping(1);
                    get_Sound().play_BGM();
                    blackie.HP = 100;
                    boss.HP = 100;
                    blackie.dead = false;
                    score_updated = false;
                    blackie.move(960.0f - blackie.get_position().x, 250.0f - blackie.get_position().y, "black_normal");
                    boss.move(1320.0f - boss.get_position().x, 250.0f - boss.get_position().y, "black_normal");
                    avartar.move(820.0f - avartar.get_position().x, 5.0f, "HPBox_final");
                    avartar1.move(1315.0f - avartar1.get_position().x, 5.0f, "HPBox_final_black");
                    dead_timer.stop();
                }
            }
            else{
                dead_timer.start();
                get_Sound().set_BGM("sfx/meowhurt");
                get_Sound().set_BGM_looping(1);
                get_Sound().play_BGM();
            }
            
            return;
        }
        
        /* end test code */
        if(blackie.thunder){
            blackie.thunder += time_step;
            m_left = false;
            m_right = false;
        }
        else if(blackie.hit){
            blackie.hit += time_step;
            m_left = false;
            m_right = false;
        }
        else if(skill_1_throw_bone || blackie.throw_fishbone){
            blackie.throw_fishbone += time_step;
            m_left = false;
            m_right = false;
        }
        else if(m_jump || blackie.jump){
            blackie.jump += time_step;
            if(blackie.jump > 40 * framestep){
                blackie.move((m_right - m_left) * time_step * 100.0f, 2.0f * time_step * 100.0f, "black_jump");
            }
            else{
                blackie.move((m_right - m_left) * time_step * 100.0f, -2.0f * time_step * 100.0f, "black_jump");
            }
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_final");
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_final_black");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        else if(m_defense){
            blackie.defend = 1;
            m_left = false;
            m_right = false;
        }
        else if(m_attack || blackie.attack){
            blackie.attack+= time_step;
        }
        else {
            blackie.move((m_right - m_left) * time_step * 100.0f, (m_down - m_up) * time_step * 100.0f, "black_normal");
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_final");
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_final_black");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        
        if(boss.hit){
            boss.hit += time_step;
            boss_left = false;
            boss_right = false;
        }
        else if(boss_thunder || boss.thunder){
            boss.thunder += time_step;
            boss_left = false;
            boss_right = false;
        }
        else if(boss_defense){
            boss.defend = 1;
            boss_left = false;
            boss_right = false;
        }
        else if(boss_attack || boss.attack){
            boss.attack+= time_step;
        }
        else {
            boss.move((boss_right - boss_left) * time_step * 100.0f, (boss_down - boss_up) * time_step * 100.0f, "black_normal");
        }
        
        if(blackie.throw_fishbone > 40 * framestep){
            blackie.throw_fishbone = 0;
            skill_1_throw_bone = false;
            actionlock = false;
            blackie_fishbones.push_back(blackie.skill_1());
        }
        
        if(boss.thunder > 40 * framestep){
            boss.thunder = 0;
            boss_thunder = false;
            boss_actionlock = false;
            thunder_list.push_back(boss.throw_thunder());
        }
        
        if(blackie.jump > 80 * framestep){
            blackie.jump = 0;
            m_jump = false;
            actionlock = false;
        }
        
        if(blackie.attack > (30 + rand()%30) * framestep){
            blackie.attack = 0;
            m_attack = false;
            actionlock = false;
        }
        
        if(boss.attack > (30 + rand()%30) * framestep){
            boss.attack = 0;
            boss_attack = false;
            boss_actionlock = false;
        }
        
        if(!boss_defense && (boss.defend == 1)){
            boss.defend = 0;
            boss_actionlock = false;
        }
        
        if(!m_defense && (blackie.defend == 1)){
            blackie.defend = 0;
            actionlock = false;
        }
        
        if(blackie.direction){
            if(m_left){
                blackie.direction = false;
            }
        }
        else {
            if(m_right){
                blackie.direction = true;
            }
        }
        
        if(boss.direction){
            if(boss_left){
                boss.direction = false;
            }
        }
        else {
            if(boss_right){
                boss.direction = true;
            }
        }
        
        for(list<Fishbone *>::iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || ((*it)->livetime > (200 * framestep))){
                delete *it;
                it = blackie_fishbones.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Thunder_arrow *>::iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 4096 || (*it)->livetime > 300 * framestep){
                delete *it;
                it = thunder_list.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 200.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -200.0f , 0.0f, "fishbone_normal");   
                }
            }
        }

        
        if(boss.attack >= 18 * framestep && boss.attack < 21 * framestep){
            
            boss.attack = 21 * framestep;
            
            float disx = boss.get_position().x - blackie.get_position().x + 15.0f;
            float disy = boss.get_position().y - blackie.get_position().y + 20.0f;
            if(abs(disx) < 75.0f && abs(disy) < 35.0f){
                if(blackie.defend && blackie.direction != boss.direction){
                    
                }
                else{
                    blackie.hit = framestep;
                    actionlock = true;
                    blackie.attack = 0.0f;
                    blackie.throw_fishbone = 0.0f;
                    blackie.HP -= 10;
                }
            }
        }
        
        if(blackie.attack >= 18 * framestep && blackie.attack < 21 * framestep){
            
            blackie.attack = 21 * framestep;
            
            float disx = boss.get_position().x - blackie.get_position().x + 15.0f;
            float disy = boss.get_position().y - blackie.get_position().y + 20.0f;
            if(abs(disx) < 75.0f && abs(disy) < 35.0f){
                if(boss.defend && blackie.direction != boss.direction){
                    
                }
                else{
                    boss.hit = framestep;
                    boss_actionlock = true;
                    boss.attack = 0.0f;
                    boss.thunder = 0.0f;
                    boss.HP -= 10;
                }
            }
        }
        
        boss.collide_with_fishbone(blackie_fishbones);
        blackie.collide_with_thunder(thunder_list);
        
        //resolve action lock glitch
        if(!blackie.throw_fishbone && !blackie.jump && !blackie.defend && !blackie.attack && !blackie.hit && actionlock){
            actionlock = false;
        }
        
        if(!boss.thunder && !boss.defend && !boss.attack && !boss.hit && boss_actionlock){
            boss_actionlock = false;
        }
    }
    
    void render() {
        get_Video().set_2d(make_pair(Point2f(blackie.get_position().x - 150.0f, 0.0f), Point2f(blackie.get_position().x + 650.0f, 600.0f)), true);
        
        world.render();
        avartar.render();
        avartar1.render();
        
        for(list<Fishbone *>::const_iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->render();
        }
        
        for(list<Thunder_arrow *>::iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->render();
        }
        
        boss.render();
        blackie.render();
        
        get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x -10.0f,67.0f), Color(0x99660099));
        
        get_Fonts()["score_font"].render_text(itoa(w_score) + ":" + itoa(b_score), Point2f(blackie.get_position().x + 200.0f,20.0f), Color(0xFFFFFFFF));
        
        if(dead_timer.is_running()){
            get_Fonts()["score_font"].render_text("Press M to restart", Point2f(blackie.get_position().x,115.0f), Color(0xFFFFFFFF));
        }
    }
    
    World world;
    BlackCat blackie;
    CatBoss boss;
    HPBox avartar, avartar1;
    
    list<Fishbone *> blackie_fishbones;
    
    list<Thunder_arrow *> thunder_list;
    
    bool actionlock;
    
    bool m_right;
    bool m_left;
    bool m_up;
    bool m_down;
    bool m_attack;
    bool m_jump;
    bool m_defense;
    
    bool boss_actionlock;
    bool boss_right;
    bool boss_left;
    bool boss_up;
    bool boss_down;
    bool boss_attack;
    bool boss_jump;
    bool boss_defense;
    bool boss_thunder;
    
    Chronometer<Time> m_chrono;
    Chronometer<Time> dead_timer;
    float m_time_passed;
    
    bool skill_1_throw_bone;
    
    int w_score;
    int b_score;
    bool m_restart;
    bool score_updated;
        
};

class Play_State3 : public Gamestate_Base {
    Play_State3(const Play_State3 &);
    Play_State3 operator=(const Play_State3 &);
    
public:
    Play_State3()
    : 
    world(Point2f(0.0f, 0.0f), Vector2f(4096.0f, 1024.0f), Global::pi * 0.0f),
    blackie(Point2f(275.0f, 300.0f), Vector2f(164.0f, 164.0f), Global::pi * 0.0f),
    boss(Point2f(1200.0f, 300.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    avartar(Point2f(275.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    avartar1(Point2f(500.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    actionlock(false),
    m_right(false),
    m_left(false),
    m_up(false),
    m_down(false),
    m_attack(false),
    m_jump(false),
    m_defense(false),
    m_time_passed(0.0f),
    skill_1_throw_bone(false),
    gameover(false),
    gameover_state(Point2f(0.0f, 0.0f), Vector2f(1024.0f, 1024.0f), Global::pi * 0.0f),
    m_restart(false),
    avartar1_visible(false)
    
    {
        set_pausable(true);
        m_chrono.start();
        
        world.type = 3;
        
        avartar1.dialog = 99;
        get_Sound().set_BGM("sfx/test");
        get_Sound().set_BGM_looping(1);
        get_Sound().play_BGM();
        
    }
    
private:
    void on_push() {
        get_Window().mouse_hide(true);
        //get_Window().mouse_grab(true);
    }
    
    void on_pop() {
        //get_Window().mouse_grab(false);
        get_Window().mouse_hide(false);
    }
    
    void on_key(const SDL_KeyboardEvent &event) {
        
        switch(event.keysym.sym) {
            case SDLK_w:
                m_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_a:
                m_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_s:
                m_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_d:
                m_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_l:
                m_defense = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_defense = false;
                }
                else{
                    actionlock = true;
                    m_left = false;
                    m_right = false;
                }
                break;
                
            case SDLK_k:
                m_jump = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_jump = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_j:
                m_attack = event.type == SDL_KEYDOWN;
                if((m_left || m_right) && m_down && !actionlock){
                    skill_1_throw_bone = true;
                    actionlock = true;
                    m_attack = false;
                }
                else if(actionlock){
                    m_attack = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_m:
                m_restart = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_p:
                boss.HP = 0;
                break;
                
            default:
                Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
                break;
        }
    }
    
    void perform_logic(){
        const float time_passed = m_chrono.seconds();
        const float time_step = time_passed - m_time_passed;
        m_time_passed = time_passed;
        
        if(gameover){
            gameover_state.visible = 1;
            if(!gameover_state.reset){
                blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
            }
            if(m_restart){
                get_Game().pop_state();
                get_Game().push_state(new Play_State3());
            }
            return;
        }
        
        if(blackie.get_position().x >= 700.0f){
            if(!avartar1_visible){
                avartar1_visible = true;
                avartar1.dialog = 16;
                avartar.move(-250.0f, 0.0f, "HPBox_final");
            }
        }
        
        if(boss.HP <= 0){
            avartar1.dialog = 21;
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    
                    gameover_state.visible = 3;
                    if(!gameover_state.reset){
                        blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
                    }
                }
            }
            else{
                dead_timer.start();
            }
            
            return;
        }
        else if(avartar1_visible){
            if(boss.HP >= 190){
                avartar1.dialog = 16;
            }
            else if(boss.HP >= 150) {
                avartar1.dialog = 17;
            }
            else if(boss.HP >= 110) {
                avartar1.dialog = 18;
            }
            else if(boss.HP >= 70) {
                avartar1.dialog = 19;
            }
            else if(boss.HP >= 30) {
                avartar1.dialog = 20;
            }
        }
        else{
            
        }
        
        if(time_passed - blackie.livetime > 1.0f) {
            
            blackie.livetime = time_passed;
            
            if(blackie.status_counter == 0){
                blackie.status_counter = 1;
            }
            else{
                blackie.status_counter = 0;
            }
            
            if(boss.state == 0){
                boss.state = 1;
            }
            else{
                boss.state = 0;
            }
        }
        /* test code for being hit */
        
        if(blackie.HP <= 0){
            blackie.HP = 0;
            blackie.dead = true;
            avartar.dialog = 15;
        }
        else{
            if(blackie.HP >= 90){
                avartar.dialog = 0;
            }
            else if(blackie.HP >= 70){
                avartar.dialog = 11;
            }
            else if(blackie.HP >= 50){
                avartar.dialog = 12;
            }
            else if(blackie.HP >= 30){
                avartar.dialog = 13;
            }
            else{
                avartar.dialog = 14;
            }
        }
        
        if(blackie.hit > 30 * framestep){
            actionlock = false;
            blackie.hit = 0;
        }
        
        if(blackie.thunder > 250 * framestep){
            blackie.thunder = 0;
        }
        
        if(blackie.dead){
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    gameover = true;
                    get_Sound().set_BGM("sfx/meowdead");
                    get_Sound().set_BGM_looping(false);
                    get_Sound().play_BGM();
                }
            }
            else{
                dead_timer.start();
                get_Sound().set_BGM("sfx/meowhurt");
                get_Sound().set_BGM_looping(false);
                get_Sound().play_BGM();
            }
            
            return;
        }
        
        /* end test code */
        if(blackie.thunder){
            blackie.thunder += time_step;
            m_left = false;
            m_right = false;
        }
        else if(blackie.hit){
            blackie.hit += time_step;
            m_left = false;
            m_right = false;
        }
        else if(skill_1_throw_bone || blackie.throw_fishbone){
            blackie.throw_fishbone += time_step;
            m_left = false;
            m_right = false;
        }
        else if(m_jump || blackie.jump){
            blackie.jump += time_step;
            if(blackie.jump > 40 * framestep){
                blackie.move((m_right - m_left) * time_step * 100.0f, 2.0f * time_step * 100.0f, "black_jump");
            }
            else{
                blackie.move((m_right - m_left) * time_step * 100.0f, -2.0f * time_step * 100.0f, "black_jump");
            }
            if(!avartar1_visible){
                avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            }
            else{
                avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_stage3");
            }
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_stage3_black");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        else if(m_defense){
            blackie.defend = 1;
            m_left = false;
            m_right = false;
        }
        else if(m_attack || blackie.attack){
            blackie.attack+= time_step;
        }
        else {
            blackie.move((m_right - m_left) * time_step * 100.0f, (m_down - m_up) * time_step * 100.0f, "black_normal");
            if(!avartar1_visible){
                avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            }
            else{
                avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_stage3");
            }
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_stage3_black");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        
        if(blackie.throw_fishbone > 40 * framestep){
            blackie.throw_fishbone = 0;
            skill_1_throw_bone = false;
            actionlock = false;
            blackie_fishbones.push_back(blackie.skill_1());
        }
        
        if(blackie.jump > 80 * framestep){
            blackie.jump = 0;
            m_jump = false;
            actionlock = false;
        }
        
        if(blackie.attack > 40 * framestep){
            blackie.attack = 0;
            m_attack = false;
            actionlock = false;
        }
        
        if(!m_defense && (blackie.defend == 1)){
            blackie.defend = 0;
            actionlock = false;
        }
        
        if(blackie.direction){
            if(m_left){
                blackie.direction = false;
            }
        }
        else {
            if(m_right){
                blackie.direction = true;
            }
        }
        
        for(list<Fishbone *>::iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || ((*it)->livetime > (200 * framestep))){
                delete *it;
                it = blackie_fishbones.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Thunder_arrow *>::iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 4096 || (*it)->livetime > 300 * framestep){
                delete *it;
                it = thunder_list.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 200.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -200.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        boss.Boss_move(blackie, time_step);
        
        if(boss.thunder > 0){
            boss.thunder += time_step;
           
            if(boss.thunder > 100 * framestep && boss.thunder < 103 * framestep){
                
                boss.thunder = 103 * framestep;
                
                thunder_list.push_back(boss.throw_thunder());
                
                float disx = boss.get_position().x - blackie.get_position().x + 15.0f;
                
                if(abs(disx) < 425.0f){
                    actionlock = true;
                    blackie.attack = 0.0f;
                    blackie.throw_fishbone = 0.0f;
                    blackie.defend = 0;
                    blackie.jump = 0.0f;
                    blackie.HP -= 15;
                    blackie.thunder = framestep;
                }
            }
            
            if(boss.thunder > 350 * framestep){
                boss.thunder = 0;
                thunder_list.push_back(boss.throw_thunder());
                thunder_list.push_back(boss.throw_thunder1());
                thunder_list.push_back(boss.throw_thunder2());
                thunder_list.push_back(boss.throw_thunder3());
                thunder_list.push_back(boss.throw_thunder4());
            }
        }
        
        if(boss.blinkcount == 1){
            
            int tmp = rand() % 5;
            
            if(tmp == 0){
                thunder_list.push_back(boss.throw_thunder());
            }
            else if(tmp == 1){
                thunder_list.push_back(boss.throw_thunder1());
            }
            else if(tmp == 2){
                thunder_list.push_back(boss.throw_thunder2());
            }
            else if(tmp == 3){
                thunder_list.push_back(boss.throw_thunder3());
            }
            else{
                thunder_list.push_back(boss.throw_thunder4());
            }
            
            boss.blinkcount = 0;
            
        }
        
        if(boss.attack >= 18 * framestep && boss.attack < 22 * framestep){
            
            boss.attack = 22 * framestep;
            
            float disx = boss.get_position().x - blackie.get_position().x + 15.0f;
            float disy = boss.get_position().y - blackie.get_position().y + 20.0f;
            if(abs(disx) < 70.0f && abs(disy) < 35.0f){
                if(blackie.defend && blackie.direction != boss.direction){
                    
                }
                else{
                    blackie.hit = framestep;
                    actionlock = true;
                    blackie.attack = 0.0f;
                    blackie.throw_fishbone = 0.0f;
                    blackie.HP -= 10;
                }
            }
        }
        
        if(boss.HP > 0){
            if(!boss.thunder){
                boss.collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 22 * framestep && blackie.attack >= 18 * framestep){
                    boss.under_attack(blackie);
                    blackie.attack = 22 * framestep;
                }
            }
        }
        else{
            boss.HP--;
        }
        
        blackie.collide_with_thunder(thunder_list);
        
        //resolve action lock glitch
        if(!blackie.throw_fishbone && !blackie.jump && !blackie.defend && !blackie.attack && !blackie.hit && actionlock){
            actionlock = false;
        }
    }
    
    void render() {
        get_Video().set_2d(make_pair(Point2f(blackie.get_position().x - 275.0f, 0.0f), Point2f(blackie.get_position().x + 525.0f, 600.0f)), true);
        
        world.render();
        avartar.render();
        avartar1.render();
        
        for(list<Fishbone *>::const_iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->render();
        }
        
        for(list<Thunder_arrow *>::iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->render();
        }
        
        boss.render();
        blackie.render();
        
        if(!avartar1_visible){
            get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x + 120.0f,67.0f), Color(0x99660099));
        }
        else{
            get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x - 130.0f,67.0f), Color(0x99660099));
        }
        gameover_state.render();
    }
    
    World world;
    BlackCat blackie;
    CatBoss boss;
    HPBox avartar, avartar1;
    
    list<Fishbone *> blackie_fishbones;
    
    list<Thunder_arrow *> thunder_list;
        
    bool actionlock;
    
    bool m_right;
    bool m_left;
    bool m_up;
    bool m_down;
    bool m_attack;
    bool m_jump;
    bool m_defense;
    
    Chronometer<Time> m_chrono;
    Chronometer<Time> dead_timer;
    float m_time_passed;
    
    bool skill_1_throw_bone;
    
    bool gameover;
    
    Gameover gameover_state;
    
    bool m_restart;
    
    bool avartar1_visible;
    
};

class Play_State2 : public Gamestate_Base {
    Play_State2(const Play_State2 &);
    Play_State2 operator=(const Play_State2 &);
    
public:
    Play_State2()
    : 
    world(Point2f(0.0f, 0.0f), Vector2f(4096.0f, 1024.0f), Global::pi * 0.0f),
    blackie(Point2f(275.0f, 250.0f), Vector2f(164.0f, 164.0f), Global::pi * 0.0f),
    avartar(Point2f(275.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    avartar1(Point2f(640.0f,5.0f), Vector2f(160.0f,80.0f),Global::pi * 0.0f),
    mouse1(Point2f(750.0f, 265.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse2(Point2f(1525.0f, 125.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse3(Point2f(1580.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse4(Point2f(2250.0f, 350.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse5(Point2f(2450.0f, 270.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse6(Point2f(3250.0f, 175.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse7(Point2f(3250.0f, 325.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer1(Point2f(1450.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer2(Point2f(2200.0f, 150.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer3(Point2f(2300.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer4(Point2f(3275.0f, 125.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer5(Point2f(3275.0f, 375.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer6(Point2f(3315.0f, 200.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer7(Point2f(3315.0f, 300.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    boss_archer(Point2f(3350.0f, 250.0f), Vector2f(136.0f, 136.0f), Global::pi * 0.0f),
    actionlock(false),
    m_right(false),
    m_left(false),
    m_up(false),
    m_down(false),
    m_attack(false),
    m_jump(false),
    m_defense(false),
    m_time_passed(0.0f),
    skill_1_throw_bone(false),
    gameover(false),
    gameover_state(Point2f(0.0f, 0.0f), Vector2f(1024.0f, 1024.0f), Global::pi * 0.0f),
    m_restart(false)
    {
        set_pausable(true);
        m_chrono.start();
        
        mouselist.push_back(&mouse1);
        mouselist.push_back(&mouse2);
        mouselist.push_back(&mouse3);
        mouselist.push_back(&mouse4);
        mouselist.push_back(&mouse5);
        mouselist.push_back(&mouse6);
        mouselist.push_back(&mouse7);
        
        archerlist.push_back(&archer1);
        archerlist.push_back(&archer2);
        archerlist.push_back(&archer3);
        archerlist.push_back(&archer4);
        archerlist.push_back(&archer5);
        archerlist.push_back(&archer6);
        archerlist.push_back(&archer7);
        
        world.type = 2;
        
        avartar1.dialog = 22;
        
        get_Sound().set_BGM("sfx/test");
        get_Sound().set_BGM_looping(false);
        get_Sound().play_BGM();
    }
    
private:
    void on_push() {
        get_Window().mouse_hide(true);
        //get_Window().mouse_grab(true);
    }
    
    void on_pop() {
        //get_Window().mouse_grab(false);
        get_Window().mouse_hide(false);
    }
    
    void on_key(const SDL_KeyboardEvent &event) {
        
        switch(event.keysym.sym) {
            case SDLK_w:
                m_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_a:
                m_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_s:
                m_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_d:
                m_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_l:
                m_defense = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_defense = false;
                }
                else{
                    actionlock = true;
                    m_left = false;
                    m_right = false;
                }
                break;
                
            case SDLK_k:
                m_jump = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_jump = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_j:
                m_attack = event.type == SDL_KEYDOWN;
                if((m_left || m_right) && m_down && !actionlock){
                    skill_1_throw_bone = true;
                    actionlock = true;
                    m_attack = false;
                }
                else if(actionlock){
                    m_attack = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_m:
                m_restart = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_p:
                blackie.HP = 100;
                break;
                
            default:
                Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
                break;
        }
    }
    
    void perform_logic(){
        const float time_passed = m_chrono.seconds();
        const float time_step = time_passed - m_time_passed;
        m_time_passed = time_passed;
        
        if(gameover){
            gameover_state.visible = 1;
            if(!gameover_state.reset){
                blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
            }
            if(m_restart){
                get_Game().pop_state();
                get_Game().push_state(new Play_State2());
            }
            return;
        }
        
        bool finish = false;
        
        if(boss_archer.HP <= 0){
            finish = true;
            avartar1.dialog = 27;
        }
        
        if(!boss_archer.alert){
            avartar1.dialog = 99;
        }
        else{ 
            if(boss_archer.HP >= 90){
                avartar1.dialog = 22;
            }
            else if(boss_archer.HP >= 70){
                avartar1.dialog = 23;
            }
            else if(boss_archer.HP >= 50){
                avartar1.dialog = 24;
            }
            else if(boss_archer.HP >= 30){
                avartar1.dialog = 25;
            }
            else if(boss_archer.HP >= 10){
                avartar1.dialog = 26;
            }
        }
        
        
        if(finish){
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    get_Sound().set_BGM("sfx/stageclear");
                    get_Sound().set_BGM_looping(true);
                    get_Sound().play_BGM();
                    
                    gameover_state.visible = 2;
                    if(!gameover_state.reset){
                        blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
                    }
                    if(m_restart){
                        get_Game().pop_state();
                        get_Game().push_state(new Play_State3());
                    }
                }
            }
            else{
                dead_timer.start();
            }
            
            return;
        }
        
        if(time_passed - blackie.livetime > 1.0f) {
            
            blackie.livetime = time_passed;
            
            if(blackie.status_counter == 0){
                blackie.status_counter = 1;
            }
            else{
                blackie.status_counter = 0;
            }
            
            for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
                if((*it)->state == 0){
                    (*it)->state = 1;
                }
                else{
                    (*it)->state = 0;
                }
            }
            
            for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
                if((*it)->state == 0){
                    (*it)->state = 1;
                }
                else{
                    (*it)->state = 0;
                }
            }
        }
        /* test code for being hit */
        
        if(blackie.HP <= 0){
            blackie.HP = 0;
            blackie.dead = true;
            avartar.dialog = 15;
        }
        else{
            if(blackie.HP >= 90){
                avartar.dialog = 0;
            }
            else if(blackie.HP >= 70){
                avartar.dialog = 11;
            }
            else if(blackie.HP >= 50){
                avartar.dialog = 12;
            }
            else if(blackie.HP >= 30){
                avartar.dialog = 13;
            }
            else{
                avartar.dialog = 14;
            }
        }
        
        if(blackie.hit > 30 * framestep){
            actionlock = true;
            blackie.hit = 0.0f;
        }
        
        if(blackie.thunder > 250 * framestep){
            blackie.thunder = 0;
        }
        
        if(blackie.dead){
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    gameover = true;
                    get_Sound().set_BGM("sfx/meowdead");
                    get_Sound().set_BGM_looping(false);
                    get_Sound().play_BGM();
                }
            }
            else{
                dead_timer.start();
                get_Sound().set_BGM("sfx/meowhurt");
                get_Sound().set_BGM_looping(false);
                get_Sound().play_BGM();
            }
            
            return;
        }
        
        /* end test code */
        if(blackie.thunder){
            blackie.thunder += time_step;
            m_left = false;
            m_right = false;
        }
        else if(blackie.hit){
            blackie.hit += time_step;
        }
        else if(skill_1_throw_bone || blackie.throw_fishbone){
            blackie.throw_fishbone += time_step;
            m_left = false;
            m_right = false;
        }
        else if(m_jump || blackie.jump){
            blackie.jump += time_step;
            if(blackie.jump > 40 * framestep){
                blackie.move((m_right - m_left) * time_step * 100.0f, 2.0f * time_step * 100.0f, "black_jump");
            }
            else{
                blackie.move((m_right - m_left) * time_step * 100.0f, -2.0f * time_step * 100.0f, "black_jump");
            }
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        else if(m_defense){
            blackie.defend = 1 ;
            m_left = false;
            m_right = false;
        }
        else if(m_attack || blackie.attack){
            blackie.attack += time_step;
            //m_left = false;
            //m_right = false;
        }
        else {
            blackie.move((m_right - m_left) * time_step * 100.0f, (m_down - m_up) * time_step * 100.0f, "black_normal");
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            avartar1.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        
        if(blackie.throw_fishbone > 40 * framestep){
            blackie.throw_fishbone = 0.0f;
            skill_1_throw_bone = false;
            actionlock = false;
            blackie_fishbones.push_back(blackie.skill_1());
        }
        
        if(blackie.jump > 80 * framestep){
            blackie.jump = 0.0f;
            m_jump = false;
            actionlock = false;
        }
        
        if(blackie.attack > 40 * framestep){
            blackie.attack = 0.0f;
            m_attack = false;
            actionlock = false;
        }
        
        if(!m_defense && (blackie.defend == 1)){
            blackie.defend = 0;
            actionlock = false;
        }
        
        if(blackie.direction){
            if(m_left){
                blackie.direction = false;
            }
        }
        else {
            if(m_right){
                blackie.direction = true;
            }
        }
        
        for(list<Fishbone *>::iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 200 * framestep){
                delete *it;
                it = blackie_fishbones.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Arrow *>::iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 200 * framestep){
                delete *it;
                it = arrowlist.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Thunder_arrow *>::iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 300 * framestep){
                delete *it;
                it = thunder_list.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * -200.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * 200.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        bool black_attack_hit_frag = false;
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->mouse_move(blackie, time_step);
            
            if((*it)->attack < 41 * framestep && (*it)->attack > 38 * framestep){
                
                (*it)->attack = 41 * framestep;
                
                float disx = (*it)->get_position().x - blackie.get_position().x - 30.0f;
                float disy = (*it)->get_position().y - blackie.get_position().y - 20.0f;
                if(abs(disx) < 65.0f && abs(disy) < 35.0f){
                    if(blackie.defend && blackie.direction == (*it)->direction){
                        
                    }
                    else{
                        blackie.hit = framestep;
                        actionlock = true;
                        blackie.attack = 0.0f;
                        blackie.throw_fishbone = 0.0f;
                        blackie.HP -= 10;
                    }
                }
            }
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack > 18 * framestep){
                    (*it)->under_attack(blackie);
                    black_attack_hit_frag = true;
                }
            }
            else{
                (*it)->HP--;
            }
        }
        
        for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
            (*it)->mouse_move(blackie, time_step);
            
            if((*it)->attack < 51 * framestep && (*it)->attack > 48 * framestep){
                
                (*it)->attack = 51 * framestep;
                arrowlist.push_back((*it)->skill_1());
            }
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack > 18 * framestep){
                    (*it)->under_attack(blackie);
                    black_attack_hit_frag = true;
                }
            }
            else{
                (*it)->HP--;
            }
        }
        
        boss_archer.mouse_move(blackie, time_step);
        
        if(boss_archer.attack < 51 * framestep && boss_archer.attack > 48 * framestep){
            
            boss_archer.attack = 51 * framestep;
            
            int tmp = rand() % 8;
            
            if(tmp <= 3){
                arrowlist.push_back(boss_archer.skill_1());
            }
            else if(tmp == 4 || tmp == 5){
                thunder_list.push_back(boss_archer.throw_thunder1());
            }
            else if(tmp == 6){
                arrowlist.push_back(boss_archer.skill_1());
                arrowlist.push_back(boss_archer.skill_2());
                arrowlist.push_back(boss_archer.skill_3());
            }
            else{
                thunder_list.push_back(boss_archer.throw_thunder1());
                thunder_list.push_back(boss_archer.throw_thunder2());
                thunder_list.push_back(boss_archer.throw_thunder3());
            }
        }
        
        if(boss_archer.HP > 0){
            boss_archer.collide_with_fishbone(blackie_fishbones);
            if(blackie.attack < 21 * framestep && blackie.attack >= 18 * framestep){
                boss_archer.under_attack(blackie);
                black_attack_hit_frag = true;
            }
        }
        else{
            boss_archer.HP--;
        }
        
        if(black_attack_hit_frag){
            blackie.attack = 21 * framestep;
        }
        
        blackie.collide_with_thunder(thunder_list);
        
        blackie.collide_with_arrow(arrowlist);
        
        //resolve action lock glitch
        if(!blackie.throw_fishbone && !blackie.jump && !blackie.defend && !blackie.attack && !blackie.hit && actionlock){
            actionlock = false;
        }
    }
    
    void render() {
        get_Video().set_2d(make_pair(Point2f(blackie.get_position().x - 275.0f, 0.0f), Point2f(blackie.get_position().x + 525.0f, 600.0f)), true);
        
        world.render();
        avartar.render();
        
        avartar1.render();
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Fishbone *>::const_iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->render();
        }
        
        for(list<Arrow *>::const_iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Thunder_arrow *>::const_iterator it = thunder_list.begin(); it != thunder_list.end(); ++it){
            (*it)->render();
        }
        
        boss_archer.render();
        
        blackie.render();
        
        get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x + 120.0f,67.0f), Color(0x99660099));
        
        gameover_state.render();
    }
    
    World world;
    BlackCat blackie;
    HPBox avartar, avartar1;
    Mouse mouse1, mouse2, mouse3, mouse4, mouse5, mouse6, mouse7;
    
    Archer archer1, archer2, archer3, archer4, archer5, archer6, archer7;
    
    Boss_Archer boss_archer;
        
    list<Mouse *> mouselist;
    
    list<Archer *> archerlist;
    
    list<Fishbone *> blackie_fishbones;
    
    list<Arrow *> arrowlist;
    
    list<Thunder_arrow *> thunder_list;
    
    bool actionlock;
    
    bool m_right;
    bool m_left;
    bool m_up;
    bool m_down;
    bool m_attack;
    bool m_jump;
    bool m_defense;
    
    Chronometer<Time> m_chrono;
    Chronometer<Time> dead_timer;
    float m_time_passed;
    
    bool skill_1_throw_bone;
    
    bool gameover;
    
    Gameover gameover_state;
    
    bool m_restart;
    
};

class Play_State : public Gamestate_Base {
    Play_State(const Play_State &);
    Play_State operator=(const Play_State &);
    
public:
    Play_State()
    : 
    world(Point2f(0.0f, 0.0f), Vector2f(8192.0f, 1024.0f), Global::pi * 0.0f),
    blackie(Point2f(275.0f, 250.0f), Vector2f(164.0f, 164.0f), Global::pi * 0.0f),
    avartar(Point2f(275.0f,5.0f), Vector2f(400.0f,200.0f),Global::pi * 0.0f),
    tree(Point2f(1900.0f, 200.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    tree1(Point2f(950.0f, 350.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    tree2(Point2f(2650.0f, 220.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    tree3(Point2f(2730.0f, 300.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    mouse1(Point2f(1250.0f, 200.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse2(Point2f(725.0f, 325.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse3(Point2f(1280.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse4(Point2f(2650.0f, 350.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse5(Point2f(2650.0f, 270.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse6(Point2f(2650.0f, 160.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse7(Point2f(3550.0f, 260.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse8(Point2f(5250.0f, 190.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse9(Point2f(5450.0f, 360.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse10(Point2f(5450.0f, 260.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    mouse11(Point2f(5400.0f, 120.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer1(Point2f(1750.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer2(Point2f(2700.0f, 150.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer3(Point2f(3600.0f, 250.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer4(Point2f(3700.0f, 350.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer5(Point2f(4400.0f, 150.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer6(Point2f(5500.0f, 270.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    archer7(Point2f(5400.0f, 160.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    actionlock(false),
    m_right(false),
    m_left(false),
    m_up(false),
    m_down(false),
    m_attack(false),
    m_jump(false),
    m_defense(false),
    m_time_passed(0.0f),
    skill_1_throw_bone(false),
    gameover(false),
    gameover_state(Point2f(0.0f, 0.0f), Vector2f(1024.0f, 1024.0f), Global::pi * 0.0f),
    m_restart(false)
    {
        set_pausable(true);
        m_chrono.start();
        treelist.push_back(&tree);
        treelist.push_back(&tree1);
        treelist.push_back(&tree2);
        treelist.push_back(&tree3);
        
        mouselist.push_back(&mouse1);
        mouselist.push_back(&mouse2);
        mouselist.push_back(&mouse3);
        mouselist.push_back(&mouse4);
        mouselist.push_back(&mouse5);
        mouselist.push_back(&mouse6);
        mouselist.push_back(&mouse7);
        mouselist.push_back(&mouse8);
        mouselist.push_back(&mouse9);
        mouselist.push_back(&mouse10);
        mouselist.push_back(&mouse11);
        
        archerlist.push_back(&archer1);
        archerlist.push_back(&archer2);
        archerlist.push_back(&archer3);
        archerlist.push_back(&archer4);
        archerlist.push_back(&archer5);
        archerlist.push_back(&archer6);
        archerlist.push_back(&archer7);
        
        world.type = 1;
        
        get_Sound().set_BGM("sfx/drum");
        get_Sound().set_BGM_looping(true);
        get_Sound().play_BGM();

        
    }
    
private:
    void on_push() {
        get_Window().mouse_hide(true);
        //get_Window().mouse_grab(true);
    }
    
    void on_pop() {
        //get_Window().mouse_grab(false);
        get_Window().mouse_hide(false);
    }
    
    void on_key(const SDL_KeyboardEvent &event) {
        
        switch(event.keysym.sym) {
            case SDLK_w:
                m_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_a:
                m_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_s:
                m_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_d:
                m_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_l:
                m_defense = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_defense = false;
                }
                else{
                    actionlock = true;
                    m_left = false;
                    m_right = false;
                }
                break;
                
            case SDLK_k:
                m_jump = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_jump = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_j:
                m_attack = event.type == SDL_KEYDOWN;
                if((m_left || m_right) && m_down && !actionlock){
                    skill_1_throw_bone = true;
                    actionlock = true;
                    m_attack = false;
                }
                else if(actionlock){
                    m_attack = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_m:
                m_restart = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_p:
                blackie.HP = 100;
                break;
                
            default:
                Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
                break;
        }
    }
    
    void perform_logic(){
        const float time_passed = m_chrono.seconds();
        const float time_step = time_passed - m_time_passed;
        m_time_passed = time_passed;
        
        if(gameover){
            gameover_state.visible = 1;
            if(!gameover_state.reset){
                blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
            }
            if(m_restart){
                get_Game().pop_state();
                get_Game().push_state(new Play_State());
            }
            return;
        }
                
        bool finish = false;
        
        if((archer4.HP <= 0) && (archer5.HP <= 0) && (archer6.HP <= 0) && (archer7.HP <= 0) && (mouse9.HP <= 0) && (mouse11.HP <= 0) && (mouse10.HP <= 0) && (mouse8.HP <= 0)){
            finish = true;
        }
        
        if(finish){
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    get_Sound().set_BGM("sfx/stageclear");
                    get_Sound().set_BGM_looping(true);
                    get_Sound().play_BGM();
                    
                    gameover_state.visible = 2;
                    if(!gameover_state.reset){
                        blackie.move(-blackie.get_position().x + 275.0f, 0.0f, "world_normal");
                    }
                    if(m_restart){
                        get_Game().pop_state();
                        get_Game().push_state(new Play_State2());
                    }
                }
            }
            else{
                dead_timer.start();
            }
            
            return;
        }
        
        if(time_passed - blackie.livetime > 1.0f) {
         
             blackie.livetime = time_passed;
             
             if(blackie.status_counter == 0){
                 blackie.status_counter = 1;
             }
             else{
                 blackie.status_counter = 0;
             }
            
             for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
                 if((*it)->state == 0){
                    (*it)->state = 1;
                 }
                 else{
                     (*it)->state = 0;
                 }
             }
            
            for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
                if((*it)->state == 0){
                    (*it)->state = 1;
                }
                else{
                    (*it)->state = 0;
                }
            }
        }
        /* test code for being hit */
        
        if(blackie.HP <= 0){
            blackie.HP = 0;
            avartar.dialog = 15;
            blackie.dead = true;
        }
        else{
            if(blackie.HP >= 90){
                avartar.dialog = 0;
            }
            else if(blackie.HP >= 70){
                avartar.dialog = 11;
            }
            else if(blackie.HP >= 50){
                avartar.dialog = 12;
            }
            else if(blackie.HP >= 30){
                avartar.dialog = 13;
            }
            else{
                avartar.dialog = 14;
            }
        }
        
        if(blackie.hit > 30 * framestep){
            actionlock = true;
            blackie.hit = 0.0f;
        }
        
        if(blackie.dead){
            if(dead_timer.is_running()){
                if(dead_timer.seconds() > 3.0f){
                    gameover = true;
                    get_Sound().set_BGM("sfx/meowdead");
                    get_Sound().set_BGM_looping(false);
                    get_Sound().play_BGM();
                }
            }
            else{
                dead_timer.start();
                get_Sound().set_BGM("sfx/meowhurt");
                get_Sound().set_BGM_looping(false);
                get_Sound().play_BGM();
            }
            
            return;
        }
            
        /* end test code */
        if(blackie.hit){
            blackie.hit += time_step;
        }
        else if(skill_1_throw_bone || blackie.throw_fishbone){
            blackie.throw_fishbone += time_step;
            m_left = false;
            m_right = false;
        }
        else if(m_jump || blackie.jump){
            blackie.jump += time_step;
            if(blackie.jump > 40 * framestep){
                blackie.move((m_right - m_left) * time_step * 100.0f, 2.0f * time_step * 100.0f, "black_jump");
            }
            else{
                blackie.move((m_right - m_left) * time_step * 100.0f, -2.0f * time_step * 100.0f, "black_jump");
            }
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        else if(m_defense){
            blackie.defend = 1 ;
            m_left = false;
            m_right = false;
        }
        else if(m_attack || blackie.attack){
            blackie.attack += time_step;
            //m_left = false;
            //m_right = false;
        }
        else {
            blackie.move((m_right - m_left) * time_step * 100.0f, (m_down - m_up) * time_step * 100.0f, "black_normal");
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        
        if(blackie.throw_fishbone > 40 * framestep){
            blackie.throw_fishbone = 0.0f;
            skill_1_throw_bone = false;
            actionlock = false;
            blackie_fishbones.push_back(blackie.skill_1());
        }
        
        if(blackie.jump > 80 * framestep){
            blackie.jump = 0.0f;
            m_jump = false;
            actionlock = false;
        }
        
        if(blackie.attack > 40 * framestep){
            blackie.attack = 0.0f;
            m_attack = false;
            actionlock = false;
        }
        
        if(!m_defense && (blackie.defend == 1)){
            blackie.defend = 0;
            actionlock = false;
        }
        
        if(blackie.direction){
            if(m_left){
                blackie.direction = false;
            }
        }
        else {
            if(m_right){
                blackie.direction = true;
            }
        }
        
        for(list<Fishbone *>::iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 200 * framestep){
                delete *it;
                it = blackie_fishbones.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Arrow *>::iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 200 * framestep){
                delete *it;
                it = arrowlist.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        bool black_attack_hit_frag = false;
        
        for(list<Tree *>::const_iterator it = treelist.begin(); it != treelist.end(); ++it){
                                    
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack > 18 * framestep){
                    (*it)->under_attack(blackie);
                    black_attack_hit_frag = true;
                }
            }
            else {
                (*it)->HP--;
            }
        }
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->mouse_move(blackie, time_step);
            
            if((*it)->attack < 41 * framestep && (*it)->attack > 38 * framestep){
                
                (*it)->attack = 41 * framestep;
                
                float disx = (*it)->get_position().x - blackie.get_position().x - 30.0f;
                float disy = (*it)->get_position().y - blackie.get_position().y - 20.0f;
                if(abs(disx) < 65.0f && abs(disy) < 35.0f){
                    if(blackie.defend && blackie.direction == (*it)->direction){

                    }
                    else{
                        blackie.hit = framestep;
                        actionlock = true;
                        blackie.attack = 0.0f;
                        blackie.throw_fishbone = 0.0f;
                        blackie.HP -= 10;
                    }
                }
            }
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack > 18 * framestep){
                    (*it)->under_attack(blackie);
                    black_attack_hit_frag = true;
                }
            }
            else{
                (*it)->HP--;
            }
        }
        
        for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
            (*it)->mouse_move(blackie, time_step);
            
            if((*it)->attack < 51 * framestep && (*it)->attack > 48 * framestep){
                
                (*it)->attack = 51 * framestep;
                arrowlist.push_back((*it)->skill_1());
            }
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack > 18 * framestep){
                    (*it)->under_attack(blackie);
                    black_attack_hit_frag = true;
                }
            }
            else{
                (*it)->HP--;
            }
        }
        
        if(black_attack_hit_frag){
            blackie.attack = 21 * framestep;
        }
        
        blackie.collide_with_arrow(arrowlist);
        
        //resolve action lock glitch
        if(!blackie.throw_fishbone && !blackie.jump && !blackie.defend && !blackie.attack && !blackie.hit && actionlock){
            actionlock = false;
        }
    }
    
    void render() {
        get_Video().set_2d(make_pair(Point2f(blackie.get_position().x - 275.0f, 0.0f), Point2f(blackie.get_position().x + 525.0f, 600.0f)), true);
        
        world.render();
        avartar.render();
        
        for(list<Tree *>::const_iterator it = treelist.begin(); it != treelist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Archer *>::const_iterator it = archerlist.begin(); it != archerlist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Fishbone *>::const_iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->render();
        }
        
        for(list<Arrow *>::const_iterator it = arrowlist.begin(); it != arrowlist.end(); ++it){
            (*it)->render();
        }
        
        blackie.render();
        
        //get_Fonts()["cat_font"].render_text("Stage: 1-1", Point2f(blackie.get_position().x + 25.0f,0.0f), Color(0x99660099));
        
        get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x + 120.0f,67.0f), Color(0x99660099));
        
        gameover_state.render();
    }
    
    World world;
    BlackCat blackie;
    HPBox avartar;
    Tree tree, tree1, tree2, tree3;
    Mouse mouse1, mouse2, mouse3, mouse4, mouse5, mouse6, mouse7, mouse8, mouse9, mouse10, mouse11;
    
    Archer archer1, archer2, archer3, archer4, archer5, archer6, archer7;
    
    list<Tree *> treelist;
    
    list<Mouse *> mouselist;
    
    list<Archer *> archerlist;
    
    list<Fishbone *> blackie_fishbones;
    
    list<Arrow *> arrowlist;
    
    bool actionlock;
    
    bool m_right;
    bool m_left;
    bool m_up;
    bool m_down;
    bool m_attack;
    bool m_jump;
    bool m_defense;
        
    Chronometer<Time> m_chrono;
    Chronometer<Time> dead_timer;
    float m_time_passed;
    
    bool skill_1_throw_bone;
    
    bool gameover;
    
    Gameover gameover_state;
    
    bool m_restart;

};

class Tutorial_State : public Gamestate_Base {
    Tutorial_State(const Tutorial_State &);
    Tutorial_State operator=(const Tutorial_State &);
    
public:
    Tutorial_State()
    : 
    world(Point2f(0.0f, 0.0f), Vector2f(8192.0f, 1024.0f), Global::pi * 0.0f),
    blackie(Point2f(275.0f, 250.0f), Vector2f(164.0f, 164.0f), Global::pi * 0.0f),
    avartar(Point2f(150.0f,12.0f), Vector2f(576.0f,144.0f),Global::pi * 0.0f),
    tree(Point2f(1200.0f, 200.0f), Vector2f(192.0f, 192.0f), Global::pi * 0.0f),
    mouse1(Point2f(2000.0f, 200.0f), Vector2f(128.0f, 128.0f), Global::pi * 0.0f),
    actionlock(false),
    m_right(false),
    m_left(false),
    m_up(false),
    m_down(false),
    m_continue(false),
    m_attack(false),
    m_jump(false),
    m_defense(false),
    m_time_passed(0.0f),
    skill_1_throw_bone(false)
    
    {
        set_pausable(true);
        m_chrono.start();
        treelist.push_back(&tree);
        
        mouselist.push_back(&mouse1);
        
        world.type = 0;
        
        avartar.dialog = 1;
        
        get_Sound().set_BGM("sfx/stageclear");
        get_Sound().set_BGM_looping(true);
        get_Sound().play_BGM();
        
    }
    
private:
    void on_push() {
        get_Window().mouse_hide(true);
        //get_Window().mouse_grab(true);
    }
    
    void on_pop() {
        //get_Window().mouse_grab(false);
        get_Window().mouse_hide(false);
    }
    
    void on_key(const SDL_KeyboardEvent &event) {
        
        switch(event.keysym.sym) {
            case SDLK_w:
                m_up = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_a:
                m_left = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_s:
                m_down = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_d:
                m_right = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_m:
                m_continue = event.type == SDL_KEYDOWN;
                break;
                
            case SDLK_l:
                m_defense = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_defense = false;
                }
                else{
                    actionlock = true;
                    m_left = false;
                    m_right = false;
                }
                break;
                
            case SDLK_k:
                m_jump = event.type == SDL_KEYDOWN;
                if(actionlock){
                    m_jump = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            case SDLK_j:
                m_attack = event.type == SDL_KEYDOWN;
                if((m_left || m_right) && m_down && !actionlock){
                    skill_1_throw_bone = true;
                    actionlock = true;
                    m_attack = false;
                }
                else if(actionlock){
                    m_attack = false;
                }
                else{
                    actionlock = true;
                }
                break;
                
            default:
                Gamestate_Base::on_key(event); // Let Gamestate_Base handle it
                break;
        }
    }
    
    void perform_logic(){
        const float time_passed = m_chrono.seconds();
        const float time_step = time_passed - m_time_passed;
        m_time_passed = time_passed;
        
        if(time_passed > 4.0f && avartar.dialog == 1){
            avartar.dialog = 2;
        }
        
        if(time_passed > 8.0f && avartar.dialog == 2){
            avartar.dialog = 3;
        }
        
        if(time_passed > 16.0f && avartar.dialog == 3){
            avartar.dialog = 4;
        }
        
        if(blackie.get_position().x > 700.0f  && avartar.dialog == 4){
            avartar.dialog = 5;
            timer1.start();
        }
        
        if(timer1.seconds() > 4.0f && avartar.dialog == 5){
            avartar.dialog = 6;
        }
        
        if(timer1.seconds() > 10.0f && avartar.dialog == 6){
            avartar.dialog = 7;
        }
        
        if(tree.HP <= 0 && avartar.dialog == 7){
            avartar.dialog = 8;
            timer2.start();
        }
        
        if(timer2.seconds() > 6.0f && avartar.dialog == 8){
            avartar.dialog = 9;
        }
        
        if(mouse1.HP <= 0 && avartar.dialog == 9){
            avartar.dialog = 10;
        }
        
        if(m_continue && avartar.dialog == 10){
            get_Game().pop_state();
            get_Game().push_state(new Play_State());
        }
        
        if(time_passed - blackie.livetime > 1.0f) {
            
            blackie.livetime = time_passed;
            
            if(blackie.status_counter == 0){
                blackie.status_counter = 1;
            }
            else{
                blackie.status_counter = 0;
            }
            
            for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
                if((*it)->state == 0){
                    (*it)->state = 1;
                }
                else{
                    (*it)->state = 0;
                }
            }
        }
        /* test code for being hit */
        
        
        if(blackie.hit > 30 * framestep){
            actionlock = true;
            blackie.hit = 0.0f;
        }
        
        /* end test code */
        if(blackie.hit){
            blackie.hit += time_step;
        }
        else if(skill_1_throw_bone || blackie.throw_fishbone){
            blackie.throw_fishbone += time_step;
            m_left = false;
            m_right = false;
        }
        else if(m_jump || blackie.jump){
            blackie.jump += time_step;
            if(blackie.jump > 40 * framestep){
                blackie.move((m_right - m_left) * time_step * 100.0f, 2.0f * time_step * 100.0f, "black_jump");
            }
            else{
                blackie.move((m_right - m_left) * time_step * 100.0f, -2.0f * time_step * 100.0f, "black_jump");
            }
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        else if(m_defense){
            blackie.defend = 1;
            m_left = false;
            m_right = false;
        }
        else if(m_attack || blackie.attack){
            blackie.attack += time_step;
            //m_left = false;
            //m_right = false;
        }
        else {
            blackie.move((m_right - m_left) * time_step * 100.0f, (m_down - m_up) * time_step * 100.0f, "black_normal");
            avartar.move((m_right - m_left) * time_step * 100.0f, 0.0f, "HPBox_normal");
            world.move((m_left - m_right) * time_step * 100.0f, 0.0f, "world_normal");
        }
        
        if(blackie.throw_fishbone > 40 * framestep){
            blackie.throw_fishbone = 0;
            skill_1_throw_bone = false;
            actionlock = false;
            blackie_fishbones.push_back(blackie.skill_1());
        }
        
        if(blackie.jump > 80 * framestep){
            blackie.jump = 0;
            m_jump = false;
            actionlock = false;
        }
        
        if(blackie.attack > 30 * framestep){
            blackie.attack = 0;
            m_attack = false;
            actionlock = false;
        }
        
        if(!m_defense && (blackie.defend == 1)){
            blackie.defend = 0;
            actionlock = false;
        }
        
        if(blackie.direction){
            if(m_left){
                blackie.direction = false;
            }
        }
        else {
            if(m_right){
                blackie.direction = true;
            }
        }
        
        for(list<Fishbone *>::iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->livetime += time_step;
            
            Point2f position = (*it)->get_position();
            if((position.x) > 8192 || (*it)->livetime > 150 * framestep){
                delete *it;
                it = blackie_fishbones.erase(it);
            }   
            else{
                if((*it)->direction){
                    (*it)->move(time_step * 150.0f , 0.0f, "fishbone_normal");
                }
                else{
                    (*it)->move(time_step * -150.0f , 0.0f, "fishbone_normal");   
                }
            }
        }
        
        for(list<Tree *>::const_iterator it = treelist.begin(); it != treelist.end(); ++it){
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack >= 18 * framestep){
                    (*it)->under_attack(blackie);
                    blackie.attack = 21 * framestep;
                }
            }
            else {
                (*it)->HP--;
            }
        }
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->mouse_move(blackie, time_step);
            
            if((*it)->attack < 41 * framestep && (*it)->attack > 38 * framestep){
                
                (*it)->attack = 41 * framestep;
                
                float disx = (*it)->get_position().x - blackie.get_position().x - 30.0f;
                float disy = (*it)->get_position().y - blackie.get_position().y - 20.0f;
                if(abs(disx) < 65.0f && abs(disy) < 35.0f){
                    if(blackie.defend && blackie.direction == (*it)->direction){
                        
                    }
                    else{
                        blackie.hit = framestep;
                        actionlock = true;
                        blackie.attack = 0.0f;
                        blackie.throw_fishbone = 0.0f;
                    }
                }
            }
            
            if((*it)->HP > 0){
                (*it)->collide_with_fishbone(blackie_fishbones);
                if(blackie.attack < 21 * framestep && blackie.attack >= 18 * framestep){
                    (*it)->under_attack(blackie);
                    blackie.attack = 21 * framestep;
                }
            }
            else{
                (*it)->HP--;
            }
        }
                
        //resolve action lock glitch
        if(!blackie.throw_fishbone && !blackie.jump && !blackie.defend && !blackie.attack && !blackie.hit && actionlock){
            actionlock = false;
        }
    }
    
    void render() {
        get_Video().set_2d(make_pair(Point2f(blackie.get_position().x - 275.0f, 0.0f), Point2f(blackie.get_position().x + 525.0f, 600.0f)), true);
        
        world.render();
        avartar.render();
        
        for(list<Tree *>::const_iterator it = treelist.begin(); it != treelist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Mouse *>::const_iterator it = mouselist.begin(); it != mouselist.end(); ++it){
            (*it)->render();
        }
        
        for(list<Fishbone *>::const_iterator it = blackie_fishbones.begin(); it != blackie_fishbones.end(); ++it){
            (*it)->render();
        }
        
        blackie.render();
        
        //get_Fonts()["cat_font"].render_text("Stage: 1-1", Point2f(blackie.get_position().x + 25.0f,0.0f), Color(0x99660099));
        //get_Fonts()["cat_font"].render_text("FPS: " + ulltoa(get_Game().get_fps()) + " xpos:  " + ulltoa(blackie.get_position().x) , Point2f(blackie.get_position().x - 75.0f,0.0f), Color(0x99660099));
        //get_Fonts()["hp_font"].render_text("HP: " + itoa(blackie.HP) + "/100", Point2f(blackie.get_position().x + 115.0f,64.0f), Color(0x99660099));
    }
    
    World world;
    BlackCat blackie;
    HPBox avartar;
    Tree tree;
    Mouse mouse1;
    
    list<Tree *> treelist;
    
    list<Mouse *> mouselist;
    
    list<Fishbone *> blackie_fishbones;
        
    bool actionlock;
    
    bool m_right;
    bool m_left;
    bool m_up;
    bool m_down;
    bool m_continue;
    bool m_attack;
    bool m_jump;
    bool m_defense;
    
    Chronometer<Time> m_chrono;
    Chronometer<Time> timer1;
    Chronometer<Time> timer2;
    float m_time_passed;
    
    bool skill_1_throw_bone;
    
};

class Instructions_State : public Widget_Gamestate {
    Instructions_State(const Instructions_State &);
    Instructions_State operator=(const Instructions_State &);
    
public:
    Instructions_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
    {
        state = 1;
        get_Sound().set_BGM("sfx/MEOW");
        get_Sound().set_BGM_looping(false);
        get_Sound().play_BGM();
    }
    
private:
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
            get_Game().pop_state();
        }
        else if(event.keysym.sym == SDLK_1 && event.state == SDL_PRESSED){
            get_Game().pop_state();
            get_Game().push_state(new Tutorial_State());
        }
        else if(event.keysym.sym == SDLK_2 && event.state == SDL_PRESSED){
            get_Game().pop_state();
            get_Game().push_state(new Play_State());
        }
        else if(event.keysym.sym == SDLK_3 && event.state == SDL_PRESSED){
            get_Game().pop_state();
            get_Game().push_state(new Play_State2());
        }
        else if(event.keysym.sym == SDLK_4 && event.state == SDL_PRESSED){
            get_Game().pop_state();
            get_Game().push_state(new Play_State3());
        }
        else if(event.keysym.sym == SDLK_UP && event.state == SDL_PRESSED){
            if(state == 2){
                state = 1;
            }
            else if(state == 3){
                state = 2;
            }
        }
        else if(event.keysym.sym == SDLK_DOWN && event.state == SDL_PRESSED){
            if(state == 2){
                state = 3;
            }
            else if(state == 1){
                state = 2;
            }
        }
        else if(event.keysym.sym == SDLK_m && event.state == SDL_PRESSED){
            if(state == 1){
                get_Game().pop_state();
                get_Game().push_state(new Tutorial_State());
            }
            else if(state == 2){
                get_Game().pop_state();
                get_Game().push_state(new Play_State());
            }
            else if(state == 3){
                state = 4;
            }
            else if(state == 4){
                get_Game().pop_state();
                get_Game().push_state(new Tutorial_State());
            }
        }
    }
    
    void render() {
        Widget_Gamestate::render();
        
        if(state == 1){
            render_image("start_1", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
        }
        else if(state == 2){
            render_image("start_2", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
        }
        else if(state == 3){
            render_image("start_3", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
        }
        else if(state == 4){
            render_image("start_Laird", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
        }
    }
    
    int state;
};

class Dualmode_State : public Widget_Gamestate {
    Dualmode_State(const Dualmode_State &);
    Dualmode_State operator=(const Dualmode_State &);
    
public:
    Dualmode_State()
    : Widget_Gamestate(make_pair(Point2f(0.0f, 0.0f), Point2f(800.0f, 600.0f)))
    {
        get_Sound().set_BGM("sfx/MEOW");
        get_Sound().set_BGM_looping(false);
        get_Sound().play_BGM();
    }
    
private:
    void on_key(const SDL_KeyboardEvent &event) {
        if(event.keysym.sym == SDLK_ESCAPE && event.state == SDL_PRESSED){
            get_Game().pop_state();
        }
        else if(event.keysym.sym == SDLK_m && event.state == SDL_PRESSED){
            get_Game().pop_state();
            get_Game().push_state(new Dual_State());
        }
    }
    
    void render() {
        Widget_Gamestate::render();
        
        render_image("dual_start", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
    }
};

class Title_State_Custom : public Title_State<Instructions_State, Dualmode_State> {
    
    public:
        Title_State_Custom()
        : Title_State<Instructions_State, Dualmode_State>("")
        {
            m_widgets.unlend_Widget(title);
            
            get_Sound().set_BGM("sfx/jungle");
            get_Sound().set_BGM_looping(true);
            get_Sound().play_BGM();
        }
        
        void render() {
            
            Title_State<Instructions_State, Dualmode_State>::render();
            
            render_image("logo", Point2f(0.0f, 0.0f), Point2f(1024.0f, 1024.0f));
        }
};

class Bootstrap {
    class Gamestate_One_Initializer : public Gamestate_Zero_Initializer {
        virtual Gamestate_Base * operator()() {
            Window::set_title("zenilib Application");
            
            get_Joysticks();   
                  
            get_Video();
            get_Textures();
            get_Fonts();
            get_Sounds();
            get_Game().joy_mouse.enabled = true;
            
            return new Title_State_Custom();
        }
    } m_goi;
    
public:
    Bootstrap() {
        g_gzi = &m_goi;
    }
} g_bootstrap;

int main(int argc, char **argv) {
    return zenilib_main(argc, argv);
}
