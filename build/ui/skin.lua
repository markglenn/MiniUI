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
	
	self.selectedHoverItem = -1;
	self.selectedItem = 0;
	
	self.highlightBar.y = 0;
	self.highlightBar.x = 0;
	
	local pos = 5;

	-- Go through all the children and position them
	for i = 0,self.childCount - 1 do
		local widget = self:GetChildWidget(1, i);

		widget.x = 10;
		widget.y = pos;

		pos = pos + self.spacing;
	end
end
				
-------------------------------------------------------------------
function SelectableList:Update( timestep )
-------------------------------------------------------------------
			
	local moveto = self.selectedItem * 30;
	if ( self.selectedHoverItem ~= -1 ) then 
		moveto = self.selectedHoverItem * 30;
	end

	local step = timestep * 150 / 400;
		
	if ( self.highlightBar.y == moveto ) then
		return;
	end
				
	if ( moveto > self.highlightBar.y ) then
		-- Move down
		self.highlightBar.y = self.highlightBar.y + step;
	else
		-- Move up
		self.highlightBar.y = self.highlightBar.y - step;
	end

	if ( math.abs(moveto - self.highlightBar.y ) <= step ) then
		self.highlightBar.y = moveto;
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
	self.widget.selectedHoverItem = split;
		
end

-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseOut ( )
-------------------------------------------------------------------
	self.widget.selectedHoverItem = -1;
		
	for i = 0,self.widget.childCount - 1 do
		self.widget:GetChildWidget(1, i).x = 10;
	end
end
				
function SelectableList_hotspot:OnMouseDown ( x, y )
	local split = math.floor(y / self.widget.spacing);
	
	if ( split < self.widget.childCount ) then
		self.widget.selectedItem = split;
	end
end
				
print "Loaded";
