--require ('ui/scripts/xpWindow');
--require ('ui/scripts/VerticalLayout');
--require ('ui/scripts/HorizontalLayout');
--require ('ui/scripts/Button');
--require ('ui/scripts/SelectableList');
require ('ui/scripts/Slideshow');
		
class "HoverHighlight" (Widget)

-------------------------------------------------------------------
function HoverHighlight:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function HoverHighlight:OnLayout( )
-------------------------------------------------------------------
	self.highlightWidget = self:GetChildWidget(0,0);
	self.highlightWidget.opacity = 0.5;
	self.animator = Animator ( );
end

-------------------------------------------------------------------
function HoverHighlight:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end
											
-------------------------------------------------------------------
function HoverHighlight:OnMouseOver ( x, y )
-------------------------------------------------------------------
	self.animator:Add ( Animate ( self.highlightWidget, "opacity", "sineInOut", 1, 500 ) );
end

-------------------------------------------------------------------
function HoverHighlight:OnMouseOut ( )
-------------------------------------------------------------------
	self.animator:Add ( Animate ( self.highlightWidget, "opacity", "sineInOut", 0.5, 500 ) );
end	

-------------------------------------------------------------------
function HoverHighlight:OnMouseDown ( x, y )
-------------------------------------------------------------------
	self.highlightWidget:Fire ( "OnClick", { } );
end
		
		
		
		
		
class "PictureViewer" (Widget)
-------------------------------------------------------------------
function PictureViewer:__init()
-------------------------------------------------------------------
	super();
	self.animator = Animator ( );
end

-------------------------------------------------------------------
function PictureViewer:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

-------------------------------------------------------------------
function PictureViewer:OnLayout ( )
-------------------------------------------------------------------
	self.previousButton = self:GetWidgetByID("previousButton");
	self.nextButton = self:GetWidgetByID("nextButton");
	
	self.previousPos = self.previousButton.x;
	self.nextPos = self.nextButton.x;
end
				
-------------------------------------------------------------------
function PictureViewer:Call( func, object )
-------------------------------------------------------------------
	if ( func == "Animate" ) then
		local prevOut = Animate ( self.previousButton, "x", "sineInOut", -50, 300 );
		local nextOut = Animate ( self.nextButton, "x", "sineInOut", 640, 300 );
	
		local delay = Delay ( 700 );
		
		local prevIn = Animate ( self.previousButton, "x", "sineInOut", self.previousPos, 300 );
		local nextIn = Animate ( self.nextButton, "x", "sineInOut", self.nextPos, 300 );
		
		nextOut:Add ( delay );
		delay:Add ( prevIn );
		delay:Add ( nextIn );
		
		self.animator:Add ( prevOut );
		self.animator:Add ( nextOut );
	end
end

		
		
		
		
		
class "AnimatedMenu" (Widget)

-------------------------------------------------------------------
function AnimatedMenu:__init()
-------------------------------------------------------------------
	super();
	self.animator = Animator ( );
end

-------------------------------------------------------------------
function AnimatedMenu:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

-------------------------------------------------------------------
function AnimatedMenu:OnLayout( )
-------------------------------------------------------------------
	self.opacity = 0;
end
		
-------------------------------------------------------------------
function AnimatedMenu:Call( func, object )
-------------------------------------------------------------------
	self:Animate ( object["id"] );
end

-------------------------------------------------------------------
function AnimatedMenu:Animate ( selectedItem )
-------------------------------------------------------------------
	math.randomseed( os.time() )
	
	local numWidgets = self:GetChildWidgetCount ( 0 );

	for i = 0,numWidgets - 1 do
		local widget = self:GetChildWidget(0, i);
		
		-- Set the delay
		local delay;
		if ( widget.id == selectedItem ) then
			delay = Delay ( 800 );
		else
			delay = Delay ( math.random(300) );
		end
		
		local anim = Animate ( widget, "y", "sineInOut", widget.y + 500, 500 );
		
		delay:Add ( anim );
		self.animator:Add ( delay );
	end
				
	local fadeDelay = Delay(800);
	
	fadeDelay:Add ( Animate ( self, "opacity", "sineInOut", 1, 500 ) );
	self.animator:Add ( fadeDelay );
				
end
				
-------------------------------------------------------------------
function AnimatedMenu:Reset ( )
-------------------------------------------------------------------
	for i = 0,numWidgets - 1 do
		local widget = self:GetChildWidget(0, i);
		
		widget.y = widget.y - 500;
		self.opacity = 0;
	end

end
print "Loaded";

