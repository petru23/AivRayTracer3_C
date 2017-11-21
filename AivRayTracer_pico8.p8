sphere = {}
sphere["center"] = {x=50, y=50, z=50}
sphere["radius"] = 30
sphere["color"] = 3

sphere2 = {}
sphere2["center"] = {x=20, y=20, z=50}
sphere2["radius"] = 40
sphere2["color"] = 4

sphere3 = {}
sphere3["center"] = {x=20, y=60, z=20}
sphere3["radius"] = 20
sphere3["color"] = 6

spheres={sphere, sphere2, sphere3}


function vlen(v)
  vx = v["x"] * v["x"]
  vy = v["y"] * v["y"]
  vz = v["z"] * v["z"]
  return sqrt(vx + vy + vz)
end

function vnorm(v)
  vn = {}
  vn["x"] = v["x"] / vlen(v)
  vn["y"] = v["y"] / vlen(v)
  vn["z"] = v["z"] / vlen(v)
  return vn 
end

function vsub(v1, v2)
  v = {}
  v["x"] = v1["x"] - v2["x"]
  v["y"] = v1["y"] - v2["y"]
  v["z"] = v1["z"] - v2["z"]
  return v
end

function vdir(v1, v2)
  return vnorm(vsub(v2, v1))
end

function vdot(v1, v2)
  return v1["x"] * v2["x"] + v1["y"] * v2["y"] + v1["z"] * v2["z"]
end

function intersects(ray)
  for _,sphere in pairs(spheres) do
    l = vsub(sphere["center"], ray["origin"])
    tca = vdot(l, ray["direction"])
    if tca > 0 then
      d = sqrt(vlen(l) * vlen(l) - tca * tca)
      if d <= sphere["radius"] then
        thc = sqrt(sphere["radius"] * sphere["radius"] - d * d)
        t0 = tca - thc
        t1 = tca + thc
        -- todo compute distance
        return sphere["color"]
      end
    end
  end
  return 0
end

cam={x=50,y=50,z=-5}

function _draw()
cls()

for y=0,100,1 do
  for x=0,100,1 do
    pixel={}
    pixel["x"]=x
    pixel["y"]=y
    pixel["z"]=0
    d = vdir(cam,pixel)
    ray={}
    ray["origin"] = cam
    ray["direction"] = d
    col = intersects(ray)
    pset(x, y, col)
  end
end
sphere["center"]["z"] -= 1
end