return {
    name = 'PlayerSystem',
    requiredComponents = { Components.Player },
    processEntity = function(self, entity, deltaTime)
        local animation = entity:get(Components.Animation)
        local velocity = entity:get(Components.Velocity)
        local sprite = entity:get(Components.Sprite)

        if Input.isActionPressed('move_right') then
            velocity.velocity.x = 100;
            animation:play('walk')
            sprite.flipY = false
        elseif Input.isActionPressed('move_left') then
            velocity.velocity.x = -100
            animation:play('walk')
            sprite.flipY = true
        else
            velocity.velocity.x = 0
            animation:play('idle')
        end
    end
}