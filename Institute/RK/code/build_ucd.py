from xml.etree import ElementTree as ET


OUT = "college/requirement_engineering/GnuCash UCD Revised.drawio"

root = ET.Element("mxfile", host="app.diagrams.net", modified="2026-10-18T00:00:00.000Z", agent="Codex", version="24.7.17", type="device")
diagram = ET.SubElement(root, "diagram", id="gnucash-use-cases", name="Use Case GnuCash")
model = ET.SubElement(diagram, "mxGraphModel", dx="1500", dy="1000", grid="1", gridSize="10", guides="1", tooltips="1", connect="1", arrows="1", fold="1", page="1", pageScale="1", pageWidth="1600", pageHeight="1000", math="0", shadow="0")
cells = ET.SubElement(model, "root")
ET.SubElement(cells, "mxCell", id="0")
ET.SubElement(cells, "mxCell", id="1", parent="0")


def vertex(id, value, style, x, y, w, h, parent="1"):
    cell = ET.SubElement(cells, "mxCell", id=id, value=value, style=style, vertex="1", parent=parent)
    ET.SubElement(cell, "mxGeometry", x=str(x), y=str(y), width=str(w), height=str(h), **{"as": "geometry"})


def edge(id, source, target, style, value=""):
    cell = ET.SubElement(cells, "mxCell", id=id, value=value, style=style, edge="1", parent="1", source=source, target=target)
    ET.SubElement(cell, "mxGeometry", relative="1", **{"as": "geometry"})


box = "rounded=0;whiteSpace=wrap;html=1;fillColor=#FFFFFF;strokeColor=#334155;strokeWidth=2;fontSize=22;fontStyle=1;verticalAlign=top;align=center;spacingTop=14;"
uc = "ellipse;whiteSpace=wrap;html=1;fillColor=#EFF6FF;strokeColor=#2563EB;strokeWidth=2;fontColor=#172554;fontSize=17;align=center;verticalAlign=middle;"
actor = "shape=umlActor;html=1;verticalLabelPosition=bottom;verticalAlign=top;fillColor=#FFFFFF;strokeColor=#334155;fontColor=#0F172A;fontSize=17;"
assoc = "endArrow=none;html=1;strokeColor=#475569;strokeWidth=2;"
general = "endArrow=block;endFill=0;endSize=15;html=1;strokeColor=#475569;strokeWidth=2;"
extend = "endArrow=open;endSize=12;dashed=1;dashPattern=7 5;html=1;strokeColor=#7C3AED;strokeWidth=2;fontSize=16;fontColor=#6D28D9;labelBackgroundColor=#FFFFFF;"

vertex("system", "GnuCash", box, 330, 80, 1120, 760)
vertex("financial", "Pengguna Keuangan", actor, 95, 245, 120, 125)
vertex("business", "Pengguna Bisnis", actor, 95, 580, 120, 125)

vertex("records", "Menetapkan dan Memelihara<br>Catatan Keuangan", uc, 425, 175, 365, 100)
vertex("reconcile", "Merekonsiliasi<br>Rekening Bank", uc, 880, 175, 365, 100)
vertex("planning", "Merencanakan dan<br>Mengevaluasi Keuangan", uc, 425, 400, 365, 100)
vertex("receivable", "Mengelola Piutang Usaha<br>(Accounts Receivable)", uc, 425, 635, 365, 100)
vertex("payable", "Mengelola Hutang Usaha<br>(Accounts Payable)", uc, 880, 635, 365, 100)
vertex("correction", "Mengoreksi Catatan<br>Keuangan", uc.replace("#EFF6FF", "#F5F3FF").replace("#2563EB", "#7C3AED"), 880, 400, 365, 100)

edge("a1", "financial", "records", assoc)
edge("a2", "financial", "reconcile", assoc)
edge("a3", "financial", "planning", assoc)
edge("a4", "business", "receivable", assoc)
edge("a5", "business", "payable", assoc)
edge("a6", "business", "financial", general)
edge("e1", "correction", "reconcile", extend, "«extend»<br>jika ada selisih")
edge("e2", "correction", "planning", extend, "«extend»<br>jika data salah")

ET.indent(root, space="  ")
ET.ElementTree(root).write(OUT, encoding="utf-8", xml_declaration=True)
print(OUT)
