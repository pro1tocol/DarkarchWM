#c.content.proxy = "http://localhost:PORT"
config.load_autoconfig(False) # ignore GUI settings

# Config ######################################################################
#c.editor.command = ['foot', '-T', 'Floating_Term', 'nvim', '{file}', '-c', 'normal {line}G{column0}l']
c.url.searchengines = {
    'DEFAULT': 'https://duckduckgo.com/?q={}',
}
c.url.start_pages = 'file:///dev/null'
c.url.default_page = 'file:///dev/null'
c.zoom.default = 150
c.zoom.levels = ["25%", "33%", "50%", "67%", "75%", "90%", "100%", "125%", "133%", "150%", "175%", "200%"]
c.fonts.web.size.default = 16 # webpage
c.fonts.default_size = '18pt' # UI

c.colors.webpage.darkmode.enabled = True
c.colors.webpage.darkmode.policy.images = 'never'
c.colors.webpage.bg = '#191919' # fix darkmode white flash
c.colors.webpage.preferred_color_scheme = 'dark'

c.tabs.show = "never" # always switching multiple

c.downloads.location.directory = "~/Downloads"
c.downloads.position = "bottom"

c.colors.completion.item.selected.match.fg = '#00ffff'
c.colors.completion.match.fg = '#00ffff'
c.colors.statusbar.normal.bg = '#6298e0'
c.colors.statusbar.command.bg = '#6298e0'
c.colors.statusbar.normal.fg = '#191919'
c.colors.statusbar.command.fg = '#191919'
c.colors.hints.bg = '#6298e0'
c.colors.hints.match.fg = '#191919'
c.colors.completion.fg = ["cyan", "white", "black"]

c.content.fullscreen.window = True # Limit fullscreen to browser window
c.content.blocking.enabled = True
c.fonts.default_family = ['SFMono Nerd Font Mono']

# privacy
c.content.javascript.enabled = True
c.content.javascript.can_close_tabs = False
c.content.javascript.can_open_tabs_automatically = False
c.content.javascript.legacy_touch_events = 'auto' # always never
c.content.canvas_reading = False
c.content.geolocation = False
c.content.webrtc_ip_handling_policy = "default-public-interface-only"
c.completion.open_categories = ['filesystem']
c.completion.cmd_history_max_items = 0
c.completion.web_history.max_items = 0
c.history_gap_interval = 0
c.auto_save.interval = 0
c.content.cache.size = 2147483647
c.content.cookies.accept = "no-unknown-3rdparty" # never no-3rdparty all
c.content.cookies.store = False

# keybindings #################################################################
config.bind('qq', 'quickmark-load')
#config.bind('cs', 'config-source')
#config.bind('gp', 'open -p')
