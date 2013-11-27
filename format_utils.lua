function hex (s)
   return string.gsub (s, '.',
                       function(c)
                          return string.format ('%02x', string.byte(c))
                       end)
end

function xpath (xp)
   local lom = require 'lxp.lom'
   local xpath = require 'xpath'

   local pt = lom.parse (page)
   return xpath.selectNodes (pt, xp)[1]
end
