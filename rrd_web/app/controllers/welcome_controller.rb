class WelcomeController < ApplicationController
  include Client
  require 'json'

  def index
  	#s = "r create 3test.rrd --start 920804400 DS:speed:COUNTER:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:10"
	file = File.read(self.get_res + '1.json')
	@data_hash = JSON.parse(file)
  	#@answer, p_out = send_from_web(s, s.length)
  
  	@img = "rrd-example3.png"
  end

  def show_image

  	
  	path = self.get_res
   	photopath = path + "#{params[:image]}.png"

   	#photopath = "/home/parallels/course/rddtool/res/#{params[:image]}.png"
   	send_file photopath, disposition: 'inline', type: 'image/png', x_sendfile: true
  end

  def get_res
  	s = "g r"
  	path, p_out = send_from_web(s, s.length)
  	path
  end
end