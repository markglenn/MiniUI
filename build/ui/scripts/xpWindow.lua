class "xpWindow" (Widget);

-------------------------------------------------------------------
function xpWindow:__init()
-------------------------------------------------------------------
	super();
	self.angle = 0;
end

-------------------------------------------------------------------
function xpWindow:Update(timestep)
-------------------------------------------------------------------
	-- Convert so we get 360 degrees in 1 second
	if ( not self.rotate ) then return end;

	self.opacity = 0.5;
	self.angle = self.angle + 360.0 * timestep / 1000.0;

	-- Are we over the 360 degrees?
	if ( self.angle > 360 ) then
		self.angle = self.angle - 360;
	end
end

class "xpWindow_hotspot" (EventArea);
-------------------------------------------------------------------
function xpWindow_hotspot:__init ( )
-------------------------------------------------------------------
	super ();
end

-------------------------------------------------------------------
function xpWindow_hotspot:OnMouseDown ( x, y )
-------------------------------------------------------------------
	self.widget.rotate = true;
end

-------------------------------------------------------------------
function xpWindow_hotspot:OnMouseUp ( )
-------------------------------------------------------------------
	self.widget.rotate = false;
end

class "xpWindow_TitleBar" (EventArea)

-------------------------------------------------------------------
function xpWindow_TitleBar:__init ( )
-------------------------------------------------------------------
	super ();
end

-------------------------------------------------------------------
function xpWindow_TitleBar:OnMouseDown ( x, y )
-------------------------------------------------------------------
	self.lastPosition = Vector2D ( x, y )
end

-------------------------------------------------------------------
function xpWindow_TitleBar:OnMouseUp ( )
-------------------------------------------------------------------
	self.dragging = false;
end


-------------------------------------------------------------------
function xpWindow_TitleBar:OnMouseUp ( )
-------------------------------------------------------------------
	self.dragging = false;
end

-------------------------------------------------------------------
function xpWindow_TitleBar:OnMouseMove ( x, y )
-------------------------------------------------------------------
	self.widget.x = self.widget.x + x - self.lastPosition.x;
	self.widget.y = self.widget.y + y - self.lastPosition.y;
end