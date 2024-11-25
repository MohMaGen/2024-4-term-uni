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
