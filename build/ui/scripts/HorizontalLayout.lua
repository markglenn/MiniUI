require "ui/scripts/Layout"

class "HorizontalLayout" (Widget)

-------------------------------------------------------------------
function HorizontalLayout:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function HorizontalLayout:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.padding = xpath.ToNumber ( widgetElement, "@padding");
end

-------------------------------------------------------------------
function HorizontalLayout:OnLayout( )
-------------------------------------------------------------------
	local childCount = self:GetChildWidgetCount (0);
	local pos = 0;

	-- Go through all the children and position them
	for i = 0,childCount - 1 do
		local widget = self:GetChildWidget(0, i);

		widget.y = 0;
		widget.x = pos;

		print ( widget.x .. " " .. widget.y );
		pos = pos + widget.width + self.padding;
	end
end