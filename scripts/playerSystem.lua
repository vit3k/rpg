return {
    name = 'PlayerSystem',
    requiredComponents = { Components.Player },
    processEntity = function(self, entity, deltaTime)
        local animation = entity:get(Components.Animation)

        if Input.isActionPressed('move_up') then
            print('test')
            animation:play('move_up')
        end
    end
}