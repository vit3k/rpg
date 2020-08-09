local MovementSystem = import('movementSystem')
local InputSystem = import('inputSystem')
local game = {}

function game:init()
	-- clearWorld() needs to be added when changing states will be available

	local inputSystem = registerSystem(InputSystem)
	local movementSystem = registerSystem(MovementSystem)

	local player = createEntity({
			transform = { x = 0, y = 0 },
			input = {}
		})
end

return game