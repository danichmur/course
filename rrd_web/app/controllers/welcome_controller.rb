class WelcomeController < ApplicationController
  include Client

  def index
  	@answer, p_out = send_from_web("g d", 3)
  end
end
