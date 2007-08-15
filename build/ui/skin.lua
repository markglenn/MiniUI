require ('ui/scripts/xpWindow');
require ('ui/scripts/VerticalLayout');
require ('ui/scripts/HorizontalLayout');
require ('ui/scripts/Button');

class "SelectableList" (Widget)

-------------------------------------------------------------------
function SelectableList:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function SelectableList:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.spacing = xpath.ToNumber ( widgetElement, "//Items/@spacing");
end

		
-------------------------------------------------------------------
function SelectableList:OnLayout( )
-------------------------------------------------------------------
	self.childCount = self:GetChildWidgetCount (1);
	local pos = 0;

	-- Go through all the children and position them
	for i = 0,self.childCount - 1 do
		local widget = self:GetChildWidget(1, i);

		widget.x = 0;
		widget.y = pos;

		pos = pos + self.spacing;
	end
end
	

class "SelectableList_hotspot" (EventArea);

-------------------------------------------------------------------
function SelectableList_hotspot:__init ( )
-------------------------------------------------------------------
	super ();
end
				
-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseHover ( x, y )
-------------------------------------------------------------------
	local split = math.floor(y / self.widget.spacing);
	
	if ( split >= self.widget.childCount ) then
		return;
	end
		
	local widget = self.widget:GetChildWidget(0, 0);
	
	widget.y = split * 30;
end

-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseOut ( )
-------------------------------------------------------------------

end
print "Loaded";
