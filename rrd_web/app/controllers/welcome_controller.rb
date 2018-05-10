class WelcomeController < ApplicationController
  include Client
  require 'json'

  def new
  end

  def index
    self.all_db
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
     #graph, p_out = send_from_web(s, s.length)
     @img = "speed3.png"
  end

end