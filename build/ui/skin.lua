--require ('ui/scripts/xpWindow');
require ('ui/scripts/VerticalLayout');
--require ('ui/scripts/HorizontalLayout');
--require ('ui/scripts/Button');
require ('ui/scripts/SelectableList');
require ('ui/scripts/Slideshow');
		
class "slideArea" (Widget);

function slideArea:__init()
	super();
end;

-------------------------------------------------------------------
function slideArea:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	local direction = xpath.ToString ( widgetElement, "@slideDirection" );
	local position = xpath.ToString ( widgetElement, "@position" );
	
	-- Setup the positioning
	self.outPosition = { x = self.x, y = self.y };
	self.inPosition = { x = self.x, y = self.y };
	
	if ( direction == "right" ) then
		self.outPosition.x = 640;
	end;
	
	if ( direction == "left" ) then
		self.outPosition.x = -self.width;
	end;
	
	if ( direction == "up" ) then
		self.outPosition.y = -self.height;
	end;
	
	if ( direction == "down" ) then
		self.outPosition.y = 480;
	end;
	
	if ( position == "out" ) then
		self.x = self.outPosition.x;
		self.y = self.outPosition.y;
	end;
	
	self.animator = Animator ( );

end;
	
-------------------------------------------------------------------
function slideArea:Call( func, object )
-------------------------------------------------------------------
	if ( func == "SlideIn" ) then
		local xanim = Animate ( self, "x", "sineInOut", self.inPosition.x, 500 )
		self.animator:Add ( xanim );
		self.animator:Add ( Animate ( self, "y", "sineInOut", self.inPosition.y, 500 ) );
		local delay = Delay ( 200 );
		
		delay:Add ( EventNotify ( self, {} ) );
		xanim:Add ( delay );
	end;
	
	if ( func == "SlideOut" ) then
		local xanim = Animate ( self, "x", "sineInOut", self.outPosition.x, 500 )
		self.animator:Add ( xanim );
		self.animator:Add ( Animate ( self, "y", "sineInOut", self.outPosition.y, 500 ) );
	
		local delay = Delay ( 200 );
		
		delay:Add ( EventNotify ( self, {} ) );
		xanim:Add ( delay );
	end;
	
	if ( func == "OnEventNotify" ) then
		if ( self.x == self.inPosition.x and self.y == self.inPosition.y ) then
			self:Fire ( "SlideInDone", { item=self } );
		else
			self:Fire ( "SlideOutDone", { item=self } );
		end;
	end;
		
end

-------------------------------------------------------------------
function slideArea:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end

class "scrollArea" (Widget)
		
-------------------------------------------------------------------------------
function scrollArea:__init()
-------------------------------------------------------------------------------
	super();
end
		
-------------------------------------------------------------------------------
function scrollArea:OnLayout()
-------------------------------------------------------------------------------

end

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
	
		local delay = Delay ( 1500 );
		
		local prevIn = Animate ( self.previousButton, "x", "sineInOut", self.previousPos, 300 );
		local nextIn = Animate ( self.nextButton, "x", "sineInOut", self.nextPos, 300 );
		
		nextOut:Add ( delay );
		delay:Add ( prevIn );
		delay:Add ( nextIn );
		
		self.animator:Add ( prevOut );
		self.animator:Add ( nextOut );
	end;
end;
	
class "adjustableBlack" (Widget);
	
-------------------------------------------------------------------
function adjustableBlack:__init()
-------------------------------------------------------------------
	super();
	self.animator = Animator ( );
end;

-------------------------------------------------------------------
function adjustableBlack:Update( timestep )
-------------------------------------------------------------------
	self.animator:Run ( timestep );
end				
				
-------------------------------------------------------------------
function adjustableBlack:Call( func, object )
-------------------------------------------------------------------
	if ( func == "FadeOut" ) then		
		self.animator:Add ( Animate ( self, "opacity", "sineInOut", 1, 300 ) );
	end;
	
	if ( func == "FadeIn" ) then
		self.animator:Add ( Animate ( self, "opacity", "sineInOut", 0, 300 ) );
	end;
end;

class "Animation" (Widget);
	
-------------------------------------------------------------------
function Animation:__init()
-------------------------------------------------------------------
	super();
	self.animator = Animator ( );
	self.isRunning = false;
end;

-------------------------------------------------------------------
function Animation:GetAnimation ( element )
-------------------------------------------------------------------
	local typeEl = xpath.ToString ( element, "self::*" );
	
	if ( typeEl ~= "Call" and typeEl ~= "Run" ) then
		return nil;
	end;
	
	local anim = {};
	
	anim.type = typeEl;
	anim.children = {};
	
	if ( typeEl == "Run" ) then
		local widgetID = xpath.ToString ( element, "@id" );
		local widget = MiniUI.FindWidget(widgetID);

		anim["widget"] = widget;
		anim["parameter"] = xpath.ToString ( element, "@parameter" );
		anim["value"] = xpath.ToNumber ( element, "@value" );
		anim["duration"] = xpath.ToNumber ( element, "@duration" );
	end;
	
	local count = xpath.ToNumber ( element, "count(child::*)" );
	
	for i = 1,count+1 do
		local search="*[" .. i .. "]";
		local val = self:GetAnimation ( xpath.ToElement( element, search ) );
		
		if ( val ~= nil ) then
			anim.children[#anim.children + 1] = val;
		end;
	end
	
	return anim;
end;	

-------------------------------------------------------------------
function Animation:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	local count = xpath.ToNumber ( widgetElement, "count(child::*)" );
	self.animations = {};
		
	for i = 1,count+1 do
		local search="*[" .. i .. "]";
		local val = self:GetAnimation ( xpath.ToElement( widgetElement, search ) );
		if ( val ~= nil ) then
			self.animations[#self.animations + 1] = val;
		end;
	end;
end;

-------------------------------------------------------------------
function Animation:Update( timestep )
-------------------------------------------------------------------
	local running = self.animator:Run ( timestep );
		
	if ( self.running and not running ) then
		self.running = false;
		self:Fire ( "AnimationDone", {} );
	end;
end;

-------------------------------------------------------------------
function Animation:Call ( func, object )
-------------------------------------------------------------------
	self.running = true;
		
	-- Here we need to build the animation from the list
	if ( func == "Run" ) then
		for i = 1, #self.animations do
			self.animator:Add ( self:CreateAnimation(self.animations[i]) );
 		end;
	end;
		
	if ( func == "OnEventNotify" )then
		
	end;
end;

-------------------------------------------------------------------
function Animation:CreateAnimation ( anim )
-------------------------------------------------------------------
	local animate = nil;
	if (anim.type == "Call" ) then
		animate = EventNotify ( self, { animation=anim } );
	elseif (anim.type == "Run" ) then
		animate = Animate ( anim.widget, anim.parameter, 
			"sineInOut", anim.value, anim.duration );
	else
		animate = Delay ( 0 );
	end;
	
	
	for i = 1, #anim.children do
  		animate:Add ( self:CreateAnimation(anim.children[i]) );
	end;
	
	return animate;
end;

print "Loaded";

