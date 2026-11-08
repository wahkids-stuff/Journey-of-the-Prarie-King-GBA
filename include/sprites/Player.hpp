#pragma once
class Player{
    public:
    bn::sprite_ptr player_sprite;
    int width = 16;
    int height = 16;
    int direction = 0;
    bool alive = true;
    bn::fixed dx = player_sprite.x();
    bn::fixed dy = player_sprite.y();
    Player(bn::sprite_ptr player_sprite) : player_sprite(player_sprite),dx(player_sprite.x()),
    dy(player_sprite.y())
    {
        
    }
    void move_check(const bn::vector<bn::rect, 8>& bounding_boxes)
    {
        bn::fixed next_x = player_sprite.x();
        bn::fixed next_y = player_sprite.y();
        
        if(bn::keypad::left_held())
        {
            next_x -= 1;
            this->direction = 3;
        }
        
        if(bn::keypad::right_held())
        {
            next_x += 1;
            this->direction = 4;
        }
        
        if(bn::keypad::up_held())
        {
            next_y -= 1;
            this->direction = 1;
        }
        
        if(bn::keypad::down_held())
        {
            next_y += 1;
            this->direction = 6;
        }
        
        bn::rect next_bounds(
            next_x.integer() - width / 2,
            next_y.integer() - height / 2,
            width,
            height
        );
        
        bool blocked = false;
        
        for(const auto& box : bounding_boxes)
        {
            if(collides(next_bounds, box))
            {
                blocked = true;
                break;
            }
        }
        
        if(! blocked)
        {
            player_sprite.set_position(next_x, next_y);
            dx = next_x;
            dy = next_y;
        }
    }
    bn::rect get_bounds() const {
        
        return bn::rect(dx.integer() - (width / 2), dy.integer() - (height / 2), width, height);
    }
    bn::fixed getX(){
        return player_sprite.x();
    }
    bn::fixed getY(){
        return player_sprite.y();
    }
    void kill(){
        alive = false;
        player_sprite.set_visible(false);
    }
};