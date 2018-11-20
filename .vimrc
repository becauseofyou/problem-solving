set cin nu rnu ts=4 sw=4 sts=4 et noswapfile nobackup
set so=100
set backspace=eol,start,indent
syntax on
set incsearch
set hlsearch
set ignorecase
set rtp+=~/.vim/bundle/Vundle.vim
call vundle#begin()
    Plugin 'gmarik/Vundle.vim'
    Plugin 'vim-airline/vim-airline'
call vundle#end()
filetype plugin indent on
let g:airline#extensions#tabline#enabled = 1
set autochdir
nmap <tab> :bn <enter>
map<f4> :!gnome-terminal -x bash -c "g++ -std=c++11 % -Wall; read" <enter> <cr> 
map<f5> :!gnome-terminal -x bash -c "./test.sh %; read" <enter> <cr>
map<f6> :!gnome-terminal -x bash -c "./a.out ; read" <enter> <cr>
colorscheme default 
set cursorline
hi CursorLine   cterm=NONE ctermbg=238 ctermfg=none
"colorscheme morning
