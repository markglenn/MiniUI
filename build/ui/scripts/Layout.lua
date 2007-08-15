class "Layout" (Widget)

-------------------------------------------------------------------
function Layout:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function Layout:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.padding = xpath.ToNumber ( widgetElement, "@padding");
	print (self.padding);
end
