Rails.application.routes.draw do
  get 'welcome/index'
  root 'welcome#index'
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
  match '/images/:image', to: "welcome#show_image", via: "get", as: :renderpic
end
