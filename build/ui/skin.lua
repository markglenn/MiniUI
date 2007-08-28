require ('ui/scripts/xpWindow');
require ('ui/scripts/VerticalLayout');
require ('ui/scripts/HorizontalLayout');
require ('ui/scripts/Button');
require ('ui/scripts/SelectableList');

class "Slideshow" (Widget)

-------------------------------------------------------------------
function Slideshow:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function Slideshow:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.animationTime = xpath.ToNumber ( widgetElement, "@time");
	
	local imageCount = xpath.ToNumber ( widgetElement, "count(//images/Image)" );
	self.descriptions = {};
	self.files = {};
	for i = 1,imageCount + 1 do
		self.descriptions[i] = xpath.ToString ( widgetElement, "//images/Image["..i.."]/@description" );
		self.files[i] = "Filename: " .. xpath.ToString ( widgetElement, "//images/Image["..i.."]/@src" );
	end
end

-------------------------------------------------------------------
function Slideshow:OnLayout( )
-------------------------------------------------------------------	
	self.selectedItem = 0;
	local childCount = self:GetChildWidgetCount (0);
	
	-- Position the highlight bar at the beginning	
	self.animator = Animator ( );

	self.hightlightBarY = self:GetChildWidget(1,0).y;
	
	-- Go through all the children and position them
	for i = 1,childCount - 1 do
		self:GetChildWidget(0, i).opacity = 0;
	end
	
	-- Find the description text fields
	self.shortDescription = self:GetWidgetByID("shortDescription");
	self.longDescription = self:GetWidgetByID("longDescription");
	
	self.shortDescription:Call ("ChangeText", {text = self.files[1] } );
	self.longDescription:Call ("ChangeText", {text = self.descriptions[1] } );
end

-------------------------------------------------------------------
function Slideshow:Call ( func, object )
-------------------------------------------------------------------
	
	if ( func == "OnEventNotify" ) then
		self:UpdateText ( );
	end
end
				
-------------------------------------------------------------------
function Slideshow:UpdateText ( )
-------------------------------------------------------------------
	if ( self.shortDescription ) then
		self.shortDescription:Call ("ChangeText", {text = self.files[self.selectedItem + 1] } );
	end
				
	if ( self.longDescription ) then
		self.longDescription:Call ("ChangeText", {text = self.descriptions[self.selectedItem + 1] } );
	end
				
end
											
-------------------------------------------------------------------
function Slideshow:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

-------------------------------------------------------------------
function Slideshow:SwitchImage ( nextImageNum )
-------------------------------------------------------------------
	local nextImage = self:GetChildWidget ( 0, nextImageNum );		
	local currentImage = self:GetChildWidget ( 0, self.selectedItem );
	
	self.animator:Add ( Animate ( nextImage, "opacity", "sineInOut", 1, self.animationTime ) );
	self.animator:Add ( Animate ( currentImage, "opacity", "sineInOut", 0, self.animationTime ) );

	local hoverMenuOut = Animate ( self:GetChildWidget(1,0), "y", "sineInOut", 480, self.animationTime / 2 );
	local hoverMenuIn = Animate ( self:GetChildWidget(1,0), "y", "bounceOut", self.hightlightBarY, self.animationTime );
	local delay = Delay ( 500 );
	local event = EventNotify ( self );
	
	hoverMenuOut:Add ( event );
	event:Add ( delay );
	delay:Add ( hoverMenuIn );

	self.animator:Add ( hoverMenuOut );

	self.selectedItem = nextImageNum;
end

class "Slideshow_hotspot" (EventArea);

-------------------------------------------------------------------
function Slideshow_hotspot:__init ( )
-------------------------------------------------------------------
	super ();
end

-------------------------------------------------------------------
function Slideshow_hotspot:OnMouseDown ( x, y )
-------------------------------------------------------------------
	self.widget:SwitchImage ( ( self.widget.selectedItem + 1 ) % self.widget:GetChildWidgetCount (0) );
end

print "Loaded";

