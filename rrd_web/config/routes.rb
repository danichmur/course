Rails.application.routes.draw do
  get 'welcome/index'
  root 'welcome#index'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  #match '/all_db', to: "welcome#all_db", via: "get"
  match '/images/:image', to: "welcome#show_image", via: "get", as: :renderpic
  match '/about_db/:name', to: "welcome#about_db", via: "get"
  match '/index', to: "welcome#all_db", via: "get"
  match '/fetch_form_json/:name', to: "welcome#fetch_form_json", via: "get"
  match '/fetch', to: "welcome#fetch", via: "get"
end
