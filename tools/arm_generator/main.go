package main

import (
	"encoding/json"
	"fmt"
	"os"
	"strconv"
	"strings"
)

type info struct {
	Hash               uint64 `json:"hash"`
	Name               string `json:"name"`
	DisplayName        string `json:"displayName"`
	DisplayDescription string `json:"displayDescription"`
}

type wpnDataMap map[string]struct {
	info
	Type       string `json:"type"`
	Components map[string]struct {
		info
		AttachmentPoint string `json:"attachmentPoint"`
	} `json:"components"`
}

var wpnData wpnDataMap

func main() {
	wpnDataF, err := os.Open("weaponData.json")
	if err != nil {
		fmt.Println(err)
		return
	}
	dec := json.NewDecoder(wpnDataF)
	err = dec.Decode(&wpnData)
	if err != nil {
		fmt.Println(err)
		return
	}
	wpnDataF.Close()

	inc, err := os.Create("../../src/arm/display_info_map.inc")
	if err != nil {
		fmt.Println(err)
		return
	}
	defer inc.Close()

	first := true

	for _, wpn := range wpnData {
		if first {
			first = false
		} else {
			inc.WriteString(",\n")
		}

		w(inc, &wpn.info)

		for _, com := range wpn.Components {
			inc.WriteString(",\n")
			w(inc, &com.info)
		}
	}

	inc.WriteString("\n")
}

func w(file *os.File, inf *info) {
	file.WriteString("{ 0x" + strings.ToUpper(strconv.FormatUint(inf.Hash, 16)) + ", { \"")

	if len(inf.DisplayName) > 0 {
		file.WriteString(inf.DisplayName)
	} else {
		file.WriteString("???")
	}

	file.WriteString("\", \"")

	if len(inf.DisplayDescription) > 0 {
		file.WriteString(inf.DisplayDescription)
	} else {
		file.WriteString("???")
	}

	file.WriteString("\" } }")
}
