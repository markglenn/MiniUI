
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
	self.highlightBar.y = -35;
	
	self.animator = Animator ( );

	-- Go through all the children and position them
	for i = 0,self.childCount - 1 do
		local widget = self:GetChildWidget(1, i);

		widget.x = 10;
		widget.y = 5 + (self.spacing * i);
	end

	self.height = 5 + (self.childCount * self.spacing );
end
				
-------------------------------------------------------------------
function SelectableList:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

-------------------------------------------------------------------
function SelectableList:OnMouseDown ( x, y )
-------------------------------------------------------------------
	local split = math.floor(y / self.spacing);
	
	if ( split >= self.childCount or split == self.selectedItem ) then
		return;
	end
	
	self.animator:Stop ( );

	self.animator:Add ( Animate ( self.highlightBar, "y",
				"bounceOut",  split * 30, 600 ) );
		
	self:Fire ( "OnSelect", { item=split } );
end

-------------------------------------------------------------------
function SelectableList:Call ( func, object )
-------------------------------------------------------------------
	if ( func == "AddText" ) then
		local widget = MiniUI.CreateWidget ( "TextArea" );	
		widget:Call ( "SetText", object );
	
		self:AddChild ( 1, widget );
		
		self.childCount = self.childCount + 1;
				
		widget.x = 10;
		widget.y = 5 + (self.spacing * (self.childCount - 1));

		self.height = 5 + (self.childCount * self.spacing );
	end
end