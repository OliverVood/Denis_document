<?php

	namespace Base\Templates\Editor;

	use Base\Templates\View;

	class Update extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div>Update tpl</div>
		<?php }

	}