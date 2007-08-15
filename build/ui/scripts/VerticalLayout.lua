require "ui/scripts/Layout"

class "VerticalLayout" (Widget)

-------------------------------------------------------------------
function VerticalLayout:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function VerticalLayout:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.padding = xpath.ToNumber ( widgetElement, "@padding");
	print (self.padding);

end

-------------------------------------------------------------------
function VerticalLayout:OnLayout( )
-------------------------------------------------------------------
	local childCount = self:GetChildWidgetCount (0);
	local pos = 0;

	-- Go through all the children and position them
	for i = 0,childCount - 1 do
		local widget = self:GetChildWidget(0, i);

		widget.x = 0;
		widget.y = pos;
		pos = pos + widget.height + self.padding;
	end
end