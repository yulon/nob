package main

import (
	"encoding/json"
	"fmt"
	"os"
)

type nfsMap map[string]map[string]struct {
	Name   string `json:"name"`
	Params []struct {
		Type string `json:"type"`
		Name string `json:"name"`
	} `json:"params"`
	Results string `json:"results"`
}

var nfs nfsMap

func main() {
	nf, err := os.Open("natives.json")
	if err != nil {
		fmt.Println(err)
		return
	}
	dec := json.NewDecoder(nf)
	err = dec.Decode(&nfs)
	if err != nil {
		fmt.Println(err)
		return
	}
	nf.Close()

	hpp, err := os.Create("../include/nob/ntv/funcs.hpp")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer hpp.Close()

	hpp.WriteString(`#pragma once

#include "func/types.hpp"
#include "func/consts.hpp"`)
	gen(hpp, true)

	cpp, err := os.Create("../src/ntv/funcs.cpp")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer cpp.Close()

	cpp.WriteString("#include <nob/ntv/funcs.hpp>")
	gen(cpp, false)
}

func gen(file *os.File, isHeadFile bool) {

	file.WriteString(`

namespace nob {
	namespace ntv {
`)
	//////////////////////////////////////////////

	for ns, fs := range nfs {
		file.WriteString("		namespace " + ns + ` {
`)
		//////////////////////////////////////
		for h, fn := range fs {
			switch fn.Results {
			case "char*":
				fn.Results = "const char*"
			case "BOOL":
				fn.Results = "bool"
			case "BOOL*":
				fn.Results = "bool*"
			}
			file.WriteString("			")
			if isHeadFile {
				file.WriteString("extern ")
			}
			file.WriteString("typed_lazy_func_t<" + fn.Results + "(")
			for i, p := range fn.Params {
				switch p.Type {
				case "char*":
					p.Type = "const char*"
				case "BOOL":
					p.Type = "bool"
				case "BOOL*":
					p.Type = "bool*"
				}
				file.WriteString(p.Type + " " + p.Name)
				if i < len(fn.Params)-1 {
					file.WriteString(", ")
				}
			}
			if fn.Name == "" {
				fn.Name = "_" + h
			}
			file.WriteString(")> " + fn.Name)
			if !isHeadFile {
				file.WriteString("(" + h + ", true)")
			}
			file.WriteString(";\n")
		}
		//////////////////////////////////////
		file.WriteString("		} /* " + ns + ` */
`)
	}

	//////////////////////////////////////////////
	file.WriteString(`	} /* ntv */
} /* nob */
`)
}
