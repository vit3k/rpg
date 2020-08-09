return {
	requiredComponents = { Components.Input },
	name = 'InputSystem',
	processEntity = function(self, entity, deltaTime)
		local input = entity:get(Components.Input)
		--local velocity = entity:get(Components.Velocity)

		if Input.isActionPressed("move_up") then
			print("test")
		end
	end
}