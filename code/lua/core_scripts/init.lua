hook_debug = true

hook_reg = {
    SVDirectConnect = 0,
    SVDropClient = 0,
}
hook_fns = {
    SVDirectConnect = {},
    SVDropClient = {},
}
hook = {}

hook_db_print = function(str)
    if hook_debug == true then
        print(str)
    end
end

hook.add = function(EventName, fn)
    if fn == nil then
        print("Attempt to add a nil hook")
        return
    end
    hook_db_print("Adding hook " .. EventName)
    if hook_reg[EventName] ~= nil then
        hook_reg[EventName] = hook_reg[EventName] + 1
        hook_db_print("New Count: " .. hook_reg[EventName])
        table.insert(hook_fns[EventName], fn)
    else
        print(EventName .. " is not a valid hook!")
    end
end

CheckHook = function(EventName, ...)
    hook_db_print("In CheckHook for " .. EventName)
    if hook_reg[EventName] ~= nil and hook_reg[EventName] > 0 then
        hook_db_print("CheckHook: " .. EventName .. " found")
        return true
    else
        hook_db_print("CheckHook: " .. EventName .. " not found")
        return false
    end
end

CallHook = function(EventName, ...)
    hook_db_print("In CallHook for " .. EventName)
    if hook_reg[EventName] ~= nil and hook_reg[EventName] > 0 then
        hook_db_print("CallHook: " .. EventName .. " found")
        for k, v in pairs(hook_fns[EventName]) do
            hook_db_print(k)
            if args == nil then
                v()
            else
                v(unpack(args))
            end
        end
    end
end
