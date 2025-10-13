#!/usr/bin/env python3
import json, sys, re
from pathlib import Path

# remove trailing commas in objects/arrays then pretty-print back
text = Path(sys.argv[1]).read_text()
# Remove trailing commas before } or ]
text = re.sub(r",\s*(}\s*)", r"\1", text)
text = re.sub(r",\s*(]\s*)", r"\1", text)
obj = json.loads(text)
Path(sys.argv[1]).write_text(json.dumps(obj, indent=2) + "\n")
print("Fixed:", sys.argv[1])
