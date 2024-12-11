#let transpose(array) = {
    let height = array.at(0).len()
    let width  = array.len()
    let ret = ()

    for y in range(height) {
        ret.push(())
        for elem in array {
            ret.at(y).push(elem.at(y))
        }
    }

    ret
}

#let push_first(array, elem) = {
    let ret = ()
    ret.push(elem)

    for elem in array { ret.push(elem) }
    
    ret
}

#let clear_csv(csv, digits: 1) = {
    csv.map(row => row.map(v => {
        let ret = calc.round(float(v.trim()), digits: digits)
        if ret.is-nan() { v } else { ret }
    }))
}
