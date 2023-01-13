<?php

	namespace Base\Templates\Editor;

	use Base\Templates\View;

	class Select extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div>Select tpl</div>
		<?php }

	}