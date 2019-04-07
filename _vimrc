set guifont=monaco:h14
set cin nu rnu ts=4 sw=4 sts=4 et noswapfile nobackup
set so=100
set backspace=eol,start,indent
syntax on
set incsearch
set hlsearch
set ignorecase
set autochdir
nmap <tab> :bn <enter>
colorscheme default 
set cursorline
hi CursorLine   cterm=NONE ctermbg=238 ctermfg=none
"colorscheme morning
colorscheme matrial-monokai
colorscheme snazzy
map <F4> :!start cmd /c g++ %<.cpp -Wall -o %< & pause <cr>
map <F5> :!start cmd /c %<  & pause<cr>
set encoding=chinese
set langmenu=zh_CN.GBK
