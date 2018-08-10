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

map<f4> :!g++ -std=c++11 % -Wall -o %<.target<cr> 
map<c-c> :! <cr>
map<f5> :!./%<.target < in<cr>


noremap <c-t> :vertical terminal <enter> 
tnoremap <c-t> exit <enter>
"tnoremap <Esc> <c-\><c-n>

colorscheme iosvkem
colorscheme desert

set cursorline
hi CursorLine   cterm=NONE ctermbg=238 ctermfg=none
