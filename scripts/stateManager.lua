local game = import('game')

return {
  state = game,

  init = function(self)
    self.state:init()
  end
}