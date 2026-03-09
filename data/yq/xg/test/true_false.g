<?xml version="1.0" encoding="UTF-8"?>
<graphxml kind="executive">
	<graph id="0"/>
	<node id="1" type="app:///xg/element/meta?key=StartXG" x="364" y="150"/>
	<port id="2" parent="1" output="true"/>
	<node id="3" type="app:///xg/element/meta?key=TrueXG" x="311.3228726679858" y="204.49190163464164"/>
	<port id="4" parent="3" input="true"/>
	<port id="5" parent="3" output="true"/>
	<node id="6" type="app:///xg/element/meta?key=FalseXG" x="415.8613335933183" y="204.49190163464164"/>
	<port id="7" parent="6" input="true"/>
	<port id="8" parent="6" output="true"/>
	<node id="9" type="app:///xg/element/meta?key=PassXG" x="415.7500823477512" y="267.565719012002"/>
	<port id="10" parent="9" input="true"/>
	<port id="11" parent="9" output="true"/>
	<node id="12" type="app:///xg/element/meta?key=DoneXG" x="311.5684160464926" y="273.4801635180876"/>
	<port id="13" parent="12" input="true"/>
	<edge id="14" source="2" target="4"/>
	<edge id="15" source="2" target="7"/>
	<edge id="16" source="5" target="13"/>
	<edge id="17" source="8" target="10"/>
</graphxml>

