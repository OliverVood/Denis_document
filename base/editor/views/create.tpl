<?php

	namespace Base\Templates\Editor;

	use Base\Templates\View;

	class Create extends View {

		public function ToVar(): string {
			$this->Start();
			$this->Render();
			return $this->Read();
		}

		public function Render() { ?>
			<div>Create tpl</div>
		<?php }

	}