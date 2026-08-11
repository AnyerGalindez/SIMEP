import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtLocation
import QtPositioning
Window {
    id: window
    width: 1150
    height: 750
    visible: true
    title: "SIMEP - Sistema de Monitoreo y Evaluación de Proyectos Humanitarios"
    color: "#f8fafc"

    // ==========================================
    // PROPIEDADES DE ESTADO GLOBAL
    // ==========================================
    property bool simulacionEnCurso: false

    // ==========================================
    // LÓGICA DE NOTIFICACIONES
    // ==========================================
    function mostrarNotificacion(mensaje) {
        textoNotificacion.text = mensaje
        toastNotificacion.visible = true
        timerNotificacion.restart()
    }

    Timer {
        id: timerNotificacion
        interval: 3500
        repeat: false
        onTriggered: toastNotificacion.visible = false
    }

    // ==========================================
    // FUNCIONES DE VALIDACIÓN LÓGICA (QML)
    // ==========================================
    function validarRegistroGeneral() {
        if (inputNombreProyecto.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa el nombre del proyecto.")
            inputNombreProyecto.forceActiveFocus()
            return false
        }
        if (inputEmpresa.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa la empresa u organización responsable.")
            inputEmpresa.forceActiveFocus()
            return false
        }
        if (inputCoordenadas.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa las coordenadas.")
            inputCoordenadas.forceActiveFocus()
            return false
        }
        if (!inputCoordenadas.acceptableInput) {
            mostrarNotificacion("⚠️ Formato de coordenadas inválido (Ej: 10.0647, -69.3570).")
            inputCoordenadas.forceActiveFocus()
            return false
        }
        if (inputDamnificados.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa el número estimado de damnificados.")
            inputDamnificados.forceActiveFocus()
            return false
        }
        return true
    }

    function validarEstructuraComposite() {
        if (inputFamilias.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa el número de familias beneficiadas.")
            inputFamilias.forceActiveFocus()
            return false
        }
        if (inputComercios.text.trim() === "") {
            mostrarNotificacion("⚠️ Por favor ingresa el número de comercios beneficiados.")
            inputComercios.forceActiveFocus()
            return false
        }
        return true
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 0

        // ==========================================
        // ENCABEZADO PRINCIPAL (HEADER)
        // ==========================================
        Rectangle {
            Layout.fillWidth: true
            Layout.preferredHeight: 70
            color: "#1e293b"

            RowLayout {
                anchors.fill: parent
                anchors.leftMargin: 25
                anchors.rightMargin: 25

                ColumnLayout {
                    spacing: 2
                    Text {
                        text: "SIMEP 🌐 Panel Principal de Control"
                        color: "#ffffff"
                        font.bold: true
                        font.pixelSize: 20
                    }
                    Text {
                        text: "Monitoreo y Evaluación de Proyectos Humanitarios en Zonas de Desastre | UNEXPO"
                        color: "#94a3b8"
                        font.pixelSize: 12
                    }
                }

                Item { Layout.fillWidth: true }

                Text {
                    text: "Desarrolladores:\nDaniel Morán | Anyer Galíndez"
                    color: "#cbd5e1"
                    font.pixelSize: 12
                    font.bold: true
                    horizontalAlignment: Text.AlignRight
                }
            }
        }

        // ==========================================
        // ÁREA DE CONTENIDO CON SCROLL
        // ==========================================
        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true
            contentWidth: availableWidth
            clip: true

            ColumnLayout {
                width: parent.width - 40
                anchors.horizontalCenter: parent.horizontalCenter
                spacing: 20

                Item { Layout.preferredHeight: 10 }

                // ------------------------------------------
                // 1. DASHBOARD & MONITOR EN TIEMPO REAL
                // ------------------------------------------
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 150
                    color: "#ffffff"
                    radius: 10
                    border.color: "#e2e8f0"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 20

                        Rectangle {
                            Layout.preferredWidth: 260
                            Layout.fillHeight: true
                            color: "#eff6ff"
                            radius: 8
                            border.color: "#bfdbfe"

                            ColumnLayout {
                                anchors.centerIn: parent
                                Text {
                                    text: "Familias Atendidas"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#1e40af"
                                }
                                Text {
                                    text: typeof simulador !== "undefined" ? simulador.valorIndicador : "0"
                                    font.pixelSize: 38
                                    font.bold: true
                                    color: "#2563eb"
                                }
                            }
                        }

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 10

                            Text {
                                text: "Monitoreo Concurrente"
                                font.pixelSize: 16
                                font.bold: true
                                color: "#0f172a"
                            }

                            RowLayout {
                                spacing: 12

                                Button {
                                    text: "▶ Iniciar Simulación"
                                    highlighted: !simulacionEnCurso
                                    onClicked: {
                                        if (simulacionEnCurso) {
                                            mostrarNotificacion("⚠️ La simulación ya se encuentra en curso.")
                                        } else {
                                            if (typeof simulador !== "undefined") {
                                                simulador.iniciarSimulacion()
                                            }
                                            simulacionEnCurso = true
                                            mostrarNotificacion("▶ Simulación de datos en vivo iniciada")
                                        }
                                    }
                                }

                                Button {
                                    text: "⏹ Detener Simulación"
                                    highlighted: simulacionEnCurso
                                    onClicked: {
                                        if (!simulacionEnCurso) {
                                            mostrarNotificacion("⚠️ La simulación ya está detenida.")
                                        } else {
                                            if (typeof simulador !== "undefined") {
                                                simulador.detenerSimulacion()
                                            }
                                            simulacionEnCurso = false
                                            mostrarNotificacion("⏹ Simulación detenida")
                                        }
                                    }
                                }
                            }
                        }
                    }
                }

                // ------------------------------------------
                // 2. REGISTRO + COMPOSITE
                // ------------------------------------------
                RowLayout {
                    Layout.fillWidth: true
                    spacing: 20

                    // Columna Izquierda: Registro de Programa y Desastre
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 350
                        color: "#ffffff"
                        radius: 10
                        border.color: "#e2e8f0"
                        border.width: 1

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 12

                            Text {
                                text: "📝 Registro de Programa y Desastre"
                                font.pixelSize: 16
                                font.bold: true
                                color: "#0f172a"
                            }

                            Rectangle { Layout.fillWidth: true; height: 1; color: "#f1f5f9" }

                            // Campo 1: Nombre
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text {
                                    text: "Nombre del Proyecto Humanitario"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#334155"
                                }
                                TextField {
                                    id: inputNombreProyecto
                                    placeholderText: "Ej. Plan de Respuesta Inundaciones 2026"
                                    Layout.fillWidth: true
                                }
                            }

                            // Campo 2: Empresa
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text {
                                    text: "Empresa / Organización Responsable"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#334155"
                                }
                                TextField {
                                    id: inputEmpresa
                                    placeholderText: "Ej. Cruz Roja / UNEXPO"
                                    Layout.fillWidth: true
                                }
                            }

                            // Campo 3: Coordenadas
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text {
                                    text: "Coordenadas del Evento (Lat, Long)"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#334155"
                                }
                                TextField {
                                    id: campoCoordenadas
                                    placeholderText: "Ej. 10.0647, -69.3570"
                                    Layout.fillWidth: true
                                    validator: RegularExpressionValidator {
                                        regularExpression: /^-?\d+(\.\d+)?,\s*-?\d+(\.\d+)?$/
                                    }
                                }
                                Button {
                                    text: "🗺️ Abrir Mapa"
                                    onClicked: {
                                        ventanaMapa.actualizarMapa(campoCoordenadas.text) // Lee el texto y lo procesa
                                        ventanaMapa.show() // Abre la ventana
                                    }
                                }
                            }

                            // Campo 4: Damnificados
                            ColumnLayout {
                                Layout.fillWidth: true
                                spacing: 2
                                Text {
                                    text: "Número Estimado de Damnificados"
                                    font.pixelSize: 12
                                    font.bold: true
                                    color: "#334155"
                                }
                                TextField {
                                    id: inputDamnificados
                                    placeholderText: "Ej. 5000"
                                    Layout.fillWidth: true
                                    validator: IntValidator { bottom: 0; top: 1000000 }
                                }
                            }

                            Item { Layout.fillHeight: true }

                            Button {
                                text: "💾 Guardar Registro General"
                                Layout.alignment: Qt.AlignRight
                                onClicked: {
                                    if (validarRegistroGeneral()) {
                                        mostrarNotificacion("✅ Registro general de datos guardado con éxito")
                                    }
                                }
                            }
                        }
                    }

                    // Columna Derecha: Estructura Composite (Actividades)
                    Rectangle {
                        Layout.fillWidth: true
                        Layout.preferredHeight: 350
                        color: "#ffffff"
                        radius: 10
                        border.color: "#e2e8f0"
                        border.width: 1

                        ColumnLayout {
                            anchors.fill: parent
                            anchors.margins: 20
                            spacing: 12

                            Text {
                                text: "🌳 Estructura de Proyecto"
                                font.pixelSize: 16
                                font.bold: true
                                color: "#0f172a"
                            }

                            Rectangle { Layout.fillWidth: true; height: 1; color: "#f1f5f9" }

                            Text {
                                text: "Carga de datos jerárquicos para el cálculo de beneficiarios."
                                font.pixelSize: 12
                                color: "#64748b"
                                wrapMode: Text.WordWrap
                                Layout.fillWidth: true
                            }

                            RowLayout {
                                Layout.fillWidth: true
                                spacing: 12

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 2
                                    Text {
                                        text: "Familias Beneficiadas"
                                        font.pixelSize: 12
                                        font.bold: true
                                        color: "#334155"
                                    }
                                    TextField {
                                        id: inputFamilias
                                        placeholderText: "Ej. 150"
                                        Layout.fillWidth: true
                                        validator: IntValidator { bottom: 0; top: 500000 }
                                    }
                                }

                                ColumnLayout {
                                    Layout.fillWidth: true
                                    spacing: 2
                                    Text {
                                        text: "Comercios Beneficiados"
                                        font.pixelSize: 12
                                        font.bold: true
                                        color: "#334155"
                                    }
                                    TextField {
                                        id: inputComercios
                                        placeholderText: "Ej. 12"
                                        Layout.fillWidth: true
                                        validator: IntValidator { bottom: 0; top: 100000 }
                                    }
                                }
                            }

                            Item { Layout.fillHeight: true }

                            Button {
                                text: "➕ Agregar Actividad"
                                Layout.alignment: Qt.AlignRight
                                onClicked: {
                                    if (validarEstructuraComposite()) {
                                        mostrarNotificacion("➕ Nueva actividad agregada al árbol del proyecto")
                                    }
                                }
                            }
                        }
                    }
                }

                // ------------------------------------------
                // 3. GENERACIÓN DE REPORTES PDF (VISITOR - C++)
                // ------------------------------------------
                Rectangle {
                    Layout.fillWidth: true
                    Layout.preferredHeight: 110
                    color: "#ffffff"
                    radius: 10
                    border.color: "#e2e8f0"
                    border.width: 1

                    RowLayout {
                        anchors.fill: parent
                        anchors.margins: 20
                        spacing: 20

                        ColumnLayout {
                            Layout.fillWidth: true
                            spacing: 4

                            Text {
                                text: "📄 Exportación de Informes"
                                font.pixelSize: 16
                                font.bold: true
                                color: "#0f172a"
                            }
                            Text {
                                text: "Genera el informe técnico en PDF procesado por el patrón Visitor en C++."
                                font.pixelSize: 12
                                color: "#64748b"
                            }
                        }

                        Button {
                            text: "📄 Generar Reporte PDF"
                            highlighted: true
                            Layout.preferredWidth: implicitWidth + 20
                            Layout.preferredHeight: 40
                            onClicked: {
                                if (validarRegistroGeneral()) {
                                    if (typeof gestorReportes !== "undefined") {
                                        var familiasVal = parseInt(inputFamilias.text.trim()) || 0
                                        var comerciosVal = parseInt(inputComercios.text.trim()) || 0

                                        var ok = gestorReportes.generarReportePDF(
                                            "Reporte_SIMEP.pdf",
                                            inputNombreProyecto.text.trim(),
                                            inputEmpresa.text.trim(),
                                            inputCoordenadas.text.trim(),
                                            parseInt(inputDamnificados.text.trim()),
                                            familiasVal,
                                            comerciosVal
                                        )
                                        if (ok) {
                                            mostrarNotificacion("📄 Reporte PDF generado e impreso correctamente")
                                        } else {
                                            mostrarNotificacion("⚠️ Error al generar el archivo PDF")
                                        }
                                    } else {
                                        mostrarNotificacion("📄 Reporte PDF generado (Modo Demostración QML)")
                                    }
                                }
                            }
                        }
                    }
                }

                Item { Layout.preferredHeight: 20 }
            }
        }
    }

    // ==========================================
    // TOAST NOTIFICACIÓN FLOTANTE (UX)
    // ==========================================
    Rectangle {
        id: toastNotificacion
        visible: false
        width: textoNotificacion.implicitWidth + 40
        height: 45
        color: "#0f172a"
        radius: 22
        opacity: 0.92

        anchors.bottom: parent.bottom
        anchors.bottomMargin: 25
        anchors.horizontalCenter: parent.horizontalCenter

        RowLayout {
            anchors.centerIn: parent
            spacing: 8

            Text {
                id: textoNotificacion
                text: ""
                color: "#ffffff"
                font.pixelSize: 13
                font.bold: true
            }
        }

        Behavior on visible {
            NumberAnimation { duration: 200 }
        }
    }
    Window  {
            id: ventanaMapa
            title: "Visor Geográfico - SIMEP"
            width: 700
            height: 500
            visible: false

            // Variable dinámica para centrar (por defecto Barquisimeto)
            property var centroActual: QtPositioning.coordinate(10.0678, -69.3474)

            // Función que procesa el texto del formulario
            function actualizarMapa(texto) {
                var partes = texto.split(","); // Corta el texto donde haya una coma
                if (partes.length === 2) {
                    var lat = parseFloat(partes[0].trim());
                    var lon = parseFloat(partes[1].trim());
                    if (!isNaN(lat) && !isNaN(lon)) {
                        centroActual = QtPositioning.coordinate(lat, lon);
                    }
                }
            }

            Map {
                anchors.fill: parent
                plugin: Plugin { name: "osm" }

                // Reemplaza los números fijos por la variable
                center: ventanaMapa.centroActual
                zoomLevel: 13

                MapCircle {
                    // Reemplaza los números fijos por la variable
                    center: ventanaMapa.centroActual
                    radius: 3000
                    color: "red"
                    opacity: 0.3
                    border.width: 2
                    border.color: "darkred"
                }
            }
        }
}
