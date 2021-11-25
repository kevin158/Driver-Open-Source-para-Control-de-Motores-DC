import React, { Component } from 'react';
import { Redirect } from 'react-router-dom';
import 'bootstrap';

class pdic extends Component{
    constructor(){
        super();
        this.state={
            posX: 0,
            posY: 0
        };
    }

    moveRight = _ => {
        if(this.state.posX === 0){
            fetch('http://localhost:8888/right')
            .then(response => {
                if(!response.ok){alert(response)}
                return response.json()
            })
            .then(response=>this.setState({posX: 1}))
            .catch(err => {
            })
            this.setState({
                posX: 1
            })
        } else{
            alert("No se puede mover mas a la derecha")
        }
    }

    moveLeft = _ => {
        if(this.state.posX === 1){
            fetch('http://localhost:8888/left')
            .then(response => {
                if(!response.ok){alert(response)}
                return response.json()
            })
            .then(response=>this.setState({posX: 0}))
            .catch(err => {
            })
            this.setState({
                posX: 0
            })
        } else{
            alert("No se puede mover mas a la izquierda")
        }
    }

    moveUp = _ => {
        if(this.state.posY === 1){
            fetch('http://localhost:8888/up')
            .then(response => {
                if(!response.ok){alert(response)}
                return response.json()
            })
            .then(response=>this.setState({posY: 0}))
            .catch(err => {
            })
            this.setState({
                posY: 0
            })
        } else{
            alert("No se puede mover mas hacia arriba")
        }
    }

    moveDown = _ => {
        if(this.state.posY === 0){
            fetch('http://localhost:8888/down')
            .then(response => {
                if(!response.ok){alert(response)}
                return response.json()
            })
            .then(response=>this.setState({posY: 1}))
            .catch(err => {
            })
            this.setState({
                posY: 1
            })
        } else{
            alert("No se puede mover mas hacia abajo")
        }
    }

    verify = _ => {
        
            fetch('http://localhost:8888/verify')
            .then(response => {
                if(!response.ok){alert(response)}
                return response.json()
            })
            .then(response=>alert("Revisar el LED en el dispositivo"))
            .catch(err => {
            })
            alert("Revisar el LED en el dispositivo")
        
    }

    

    

    render(){
        return(
            <div id="page_wrapper">

                <div id="page_content" className="container" style-prop-object="height: 1000px;" >
                            <div className="contain1">
                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => alert("Utilice los botones con flechas para realizar un movimiento correspondiente en el dispositivo. Utilice el boton de verificacion para comprobar el correcto funcionamiento del sistema.")} >
                            <i className="fa fa-question" aria-hidden="true"></i> Ayuda </button>

                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => alert("Instituto Tecnologico de Costa Rica, Area Academica de Ingenieria en Computadores. Proyecto: Driver Open SOurce para Control de Motores DC, Kevin Acuna Mena.")} >
                            <i className="fa fa-info" aria-hidden="true"></i> Info </button>
                            </div>

                            <div className='contain2'></div>

                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => this.verify()} >
                            <i className="fa fa-exchange" aria-hidden="true"></i> Verificacion </button>
                            </div>
                            </div>

                            <div className="contain1">
                            <div className='contain2'></div>

                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => this.moveUp()} >
                            <i className="fa fa-arrow-up" aria-hidden="true"></i> Arriba </button>
                            </div>

                            <div className='contain2'></div>
                            </div>

                            <div className="contain1">
                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => this.moveLeft()} >
                            <i className="fa fa-arrow-left" aria-hidden="true"></i> Izquierda </button>
                            </div>

                            <div className='contain2'></div>

                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => this.moveRight()} >
                            <i className="fa fa-arrow-right" aria-hidden="true"></i> Derecha </button>
                            </div>
                            </div>

                            <div className="contain1">
                            <div className='contain2'></div>

                            <div className='contain2'>
                            <button type="submit" className="btn btn-primary btn-lg" id="btn" onClick={() => this.moveDown()} >
                            <i className="fa fa-arrow-down" aria-hidden="true"></i> Abajo </button>
                            </div>

                            <div className='contain2'></div>
                            </div>

                            <div className="contain1">

                            <div className='contain2'></div>
                            </div>
                      
                    
                </div>
            </div>
        )
    }
}
export default pdic;