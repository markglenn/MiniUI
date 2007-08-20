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

	self.selectedItem = -1;
	
	-- Position the highlight bar at the beginning
	self.highlightBar.x = 0;
	self.highlightBar.y = self.selectedItem * 30;
	
	self.animator = Animator ( );

	-- Go through all the children and position them
	for i = 0,self.childCount - 1 do
		local widget = self:GetChildWidget(1, i);

		widget.x = 10;
		widget.y = 5 + (self.spacing * i);
	end
end
				
-------------------------------------------------------------------
function SelectableList:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

class "SelectableList_hotspot" (EventArea);

-------------------------------------------------------------------
function SelectableList_hotspot:__init ( )
-------------------------------------------------------------------
	super ();
	self.slidetimer = 200;
end

-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseOver ( )
-------------------------------------------------------------------
	self.split = -1;
end
				
-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseHover ( x, y )
-------------------------------------------------------------------
	local split = math.floor(y / self.widget.spacing);
		
	if ( split >= self.widget:GetChildWidgetCount(1) ) then return end;
		
	if ( self.split ~= split ) then
		local onwidget = self.widget:GetChildWidget(1, split);
		local onanim = Animate(onwidget, "x", "sineInOut", 20, self.slidetimer );
		self.widget.animator:Add ( onanim );
		
		if ( self.split ~= -1 ) then
			local offwidget = self.widget:GetChildWidget(1, self.split);
			local offanim = Animate(offwidget, "x", "sineInOut", 10, self.slidetimer );
			self.widget.animator:Add ( offanim );
		end
		
		self.split = split;
	end		
end

-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseOut ( )
-------------------------------------------------------------------
	if ( self.split ~= -1 ) then
		local offwidget = self.widget:GetChildWidget(1, self.split);
		local offanim = Animate(offwidget, "x", "sineInOut", 10, self.slidetimer );
		self.widget.animator:Add ( offanim );
	end
	
	self.split = -1;
end
-------------------------------------------------------------------
function SelectableList_hotspot:OnMouseDown ( x, y )
-------------------------------------------------------------------
	local split = math.floor(y / self.widget.spacing);
	
	if ( split >= self.widget.childCount or split == self.widget.selectedItem ) then
		return;
	end
	
	self.widget.animator:Stop ( );

	self.widget.animator:Add ( Animate ( self.widget.highlightBar, "y",
				"sineInOut",  split * 30, 200 ) );
end
				
print "Loaded";
