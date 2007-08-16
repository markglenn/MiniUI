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
	self.highlightBar = self:GetChildWidget(0, 0);
	
	self.highlightBar.opacity = 0;
	
	local pos = 5;

	-- Go through all the children and position them
	for i = 0,self.childCount - 1 do
		local widget = self:GetChildWidget(1, i);

		widget.x = 10;
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
	
	self.widget.highlightBar.opacity = 1;
	for i = 0,self.widget.childCount - 1 do
		self.widget:GetChildWidget(1, i).x = 10;
	end
				
	self.widget:GetChildWidget(1, split).x = 30;
	self.widget.highlightBar.x = 20;
	self.widget.highlightBar.y = split * 30;
end

-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseOut ( )
-------------------------------------------------------------------
	self.widget.highlightBar.opacity = 0;
		
	for i = 0,self.widget.childCount - 1 do
		self.widget:GetChildWidget(1, i).x = 10;
	end
end
print "Loaded";
