class WelcomeController < ApplicationController
  include Client
  require 'json'

  def index
    self.all_db
  	#s = "r create 3test.rrd --start 920804400 DS:speed:COUNTER:600:U:U RRA:AVERAGE:0.5:1:24 RRA:AVERAGE:0.5:6:10"
  	#@answer, p_out = send_from_web(s, s.length)
	
	#file = File.read(self.get_res + '1.json')
	#@data_hash = JSON.parse(file)
  #	@img = "rrd-example3.png"
  	
  end

  def show_image
  	path = self.get_res
   	photopath = path + "#{params[:image]}.png"
   	send_file photopath, disposition: 'inline', type: 'image/png', x_sendfile: true
  end

  def get_res
  	s = "g r"
  	path, p_out = send_from_web(s, s.length)
  	path
  end

  def all_db
    s = "a"
    @all_db, p_out = send_from_web(s, s.length)
    @all_db = @all_db.split("\n")
  end

  def about_db
    @name = "#{params[:name]}"
    s = "r info #{params[:name]}"
    @descr, p_out = send_from_web(s, s.length)
    @descr = @descr.split("\n")
  end

  def fetch
    @name = "speed"
    s = "-r fetch -n speed.rrd -c AVERAGE -s 920804400 -e 920809200 -f file.json"
    @fetch, p_out = send_from_web(s, s.length)
    file = File.read(self.get_res + 'file.json')
    @data_hash = JSON.parse(file)
    self.graph
  end

  def fetch_form_json
    @name = "#{params[:name]}"
  end

  def graph
     s = "graph speed3.png --start 920804400--end 920808000 --vertical-label km/h DEF:myspeed=/home/parallels/rrdtool/rddtool/data/example:speed:AVERAGE CDEF:kmh=myspeed,3600,* CDEF:fast=kmh,100,GT,kmh,0,IF CDEF:good=kmh,100,GT,0,kmh,IF HRULE:100#0000FF:\"Maximum allowed\" AREA:good#00FF00:\"Good speed\" AREA:fast#FF0000:\"Too fast\""
     graph, p_out = send_from_web(s, s.length)
     @img = "speed3.png"
  end

end