ml_get: invalid lnum: 6

## Reproduce

```vim
vim tt.cpp
:Leaderf file " choose ttt.cpp
:Leaderf file " this will trigger error
```

+ dotfiles commit: 4b3bbf0
+ vim version: local/gvim-lily 8.2.2340-1

.vimrc:

```vim
" 定义快捷键的前缀，即<leader>
let mapleader=" "
command! BufOnly silent! execute "%bd|e#|bd#"
nnoremap <silent> <leader>bo :BufOnly<CR>

call plug#begin('~/.vim/plugged')
Plug 'Yggdroot/LeaderF', { 'do': ':LeaderfInstallCExtension' }
Plug 'skywind3000/asyncrun.vim'
Plug 'skywind3000/asynctasks.vim'
call plug#end()

set hidden
let g:Lf_RootMarkers = ['.project', '.root', '.svn', '.git', '.hg']

let g:Lf_GtagsAutoGenerate = 1
let g:Lf_Gtagslabel = 'native-pygments'
let g:Lf_GtagsSource = 2
let g:Lf_GtagsfilesCmd = {
        \ '.git': 'git ls-files --recurse-submodules',
        \ '.hg': 'hg files',
        \ 'default': 'rg --no-messages --files'
        \}

let g:Lf_DefaultExternalTool='rg'
let g:Lf_IgnoreCurrentBufferName = 1
let g:Lf_NormalMap = {
	\ "File":   [["<ESC>", ':exec g:Lf_py "fileExplManager.quit()"<CR>']],
	\ "Buffer": [["<ESC>", ':exec g:Lf_py "bufExplManager.quit()"<CR>']],
	\ "Mru":    [["<ESC>", ':exec g:Lf_py "mruExplManager.quit()"<CR>']],
	\ "Tag":    [["<ESC>", ':exec g:Lf_py "tagExplManager.quit()"<CR>']],
	\ "BufTag":    [["<ESC>", ':exec g:Lf_py "bufTagExplManager.quit()"<CR>']],
	\ "Function":    [["<ESC>", ':exec g:Lf_py "functionExplManager.quit()"<CR>']],
	\ "Colorscheme":    [["<ESC>", ':exec g:Lf_py "colorschemeExplManager.quit()"<CR>']],
	\ }

let g:Lf_MruMaxFiles = 2048
let g:Lf_StlSeparator = { 'left': "\ue0b0", 'right': "\ue0b2", 'font': ''}
let g:Lf_StlColorscheme = 'powerline'

let g:Lf_WorkingDirectoryMode = 'Ac'
let g:Lf_WindowHeight = 0.30
let g:Lf_ShowRelativePath = 1
let g:Lf_CursorBlink = 0
let g:Lf_JumpToExistingWindow = 0

let g:Lf_WildIgnore = {
            \ 'dir': ['.svn','.git','.hg'],
            \ 'file': ['*.sw?','~$*','*.bak','*.exe','*.o','*.so','*.py[co]']
			\ }

let g:Lf_MruFileExclude = ['*.so', '*.exe', '*.py[co]', '*.sw?', '~$*', '*.bak', '*.tmp', '*.dll']

if (exists('*popup_create') && has('patch-8.1.2000')) || has('nvim-0.4')
	let g:Lf_WindowPosition = 'popup'
    let g:Lf_PreviewInPopup = 1
endif

"----------------------------------------------------------------------
" keymap
"----------------------------------------------------------------------
let g:Lf_ShortcutF = '<leader>e'
" noremap <leader>el :LeaderfFile %:p:h<CR>
let g:Lf_ShortcutB = '<leader>fb'

let g:asyncrun_open = 6
let g:asyncrun_rootmarks = ['.git', '.svn', '.root', '.project', '.hg']

" https://github.com/skywind3000/asynctasks.vim/blob/master/README-cn.md#%E5%A4%9A%E7%A7%8D%E8%BF%90%E8%A1%8C%E6%A8%A1%E5%BC%8F
let g:asynctasks_term_pos = 'bottom'
let g:asynctasks_term_rows = 10    " 设置纵向切割时，高度为 10
let g:asynctasks_term_cols = 80    " 设置横向切割时，宽度为 80

" https://github.com/skywind3000/asynctasks.vim/wiki/UI-Integration#leaderf
noremap <tab>t :Leaderf --nowrap task<cr>
let g:asynctasks_profile = 'release'

"----------------------------------------------------------------------
" source task
"----------------------------------------------------------------------
function! LfTaskSource(...)
	let rows = asynctasks#source(&columns * 48 / 100)
	let source = []
	for row in rows
		let name = row[0]
		let source += [name . '  ' . row[1] . '  : ' . row[2]]
	endfor
	return source
endfunc


function! LfTaskAccept(line, arg)
	let pos = stridx(a:line, '<')
	if pos < 0
		return
	endif
	let name = strpart(a:line, 0, pos)
	let name = substitute(name, '^\s*\(.\{-}\)\s*$', '\1', '')
	redraw
	if name != ''
		exec "AsyncTask " . name
	endif
endfunc

function! LfTaskDigest(line, mode)
	let pos = stridx(a:line, '<')
	if pos < 0
		return [a:line, 0]
	endif
	let name = strpart(a:line, 0, pos)
	return [name, 0]
endfunc

function! LfWinInit(...)
	setlocal nonumber
	setlocal nowrap
endfunc


let g:Lf_Extensions = get(g:, 'Lf_Extensions', {})
let g:Lf_Extensions.task = {
			\ 'source': string(function('LfTaskSource'))[10:-3],
			\ 'accept': string(function('LfTaskAccept'))[10:-3],
			\ 'get_digest': string(function('LfTaskDigest'))[10:-3],
			\ 'highlights_def': {
			\     'Lf_hl_funcScope': '^\S\+',
			\     'Lf_hl_funcDirname': '^\S\+\s*\zs<.*>\ze\s*:',
			\ },
			\ 'after_enter': string(function('LfWinInit'))[10:-3],
		\ }
```
