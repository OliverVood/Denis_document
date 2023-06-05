<?php

	namespace Base\Editor\Skins\Edit;

	use Base\Editor\Skins\SkinEditHTMLElement;
	use Base\Templates\Buffering;

	class TextArea extends SkinEditHTMLElement {

		public function __construct(string $title, string $name, string $default = '') {
			parent::__construct($title, $name, $default);
		}

		public function ToVar(mixed $value = null): string {
			Buffering::Start();
			$this->Render($value ?? $this->default);
			return Buffering::Read();
		}

		public function Render(string $value): void { ?>
			<textarea name = "<?= $this->name; ?>"><?= $value; ?></textarea>
		<?php }

	}