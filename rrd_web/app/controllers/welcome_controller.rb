class WelcomeController < ApplicationController
  include Client

  def index
  	s = "r create 3test.rrd --start 920804400 DS:speed:COUNTER:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:10"

  	@answer, p_out = send_from_web(s, s.length)
  	puts @answer
  end
end
