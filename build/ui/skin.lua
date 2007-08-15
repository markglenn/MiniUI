require ('ui/scripts/xpWindow');
require ('ui/scripts/VerticalLayout');
require ('ui/scripts/HorizontalLayout');

class "Button" (Widget)

-------------------------------------------------------------------
function Button:__init()
-------------------------------------------------------------------
	super();
end

-------------------------------------------------------------------
function Button:OnLoad(skinElement, widgetElement)
-------------------------------------------------------------------
	self.nohover = {
			self:GetGraphicalRect("left"),
			self:GetGraphicalRect("center"),
			self:GetGraphicalRect("right") };
	self.hover = {
			self:GetGraphicalRect("left-hover"),
			self:GetGraphicalRect("center-hover"),
			self:GetGraphicalRect("right-hover") };
end

class "Button_hotspot" (EventArea);

-------------------------------------------------------------------
function Button_hotspot:__init ( )
-------------------------------------------------------------------
	super ();
end

-------------------------------------------------------------------
function Button_hotspot:OnMouseOver ( )
-------------------------------------------------------------------
	for i=1,#self.widget.hover do
		self.widget.hover[i].isVisible = true;
	end

	for i=1,#self.widget.nohover do
		self.widget.nohover[i].isVisible = false;
	end

	self.widget:UpdateRenderable ( );
end

-------------------------------------------------------------------
function Button_hotspot:OnMouseOut ( )
-------------------------------------------------------------------
	for i=1,#self.widget.nohover do
		self.widget.nohover[i].isVisible = true;
	end

	for i=1,#self.widget.hover do
		self.widget.hover[i].isVisible = false;
	end

	self.widget:UpdateRenderable ( );
end

print "Loaded";
